/*
 * Copyright (C) 2022, Linaro Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>
#include <linux/qrtr.h>
#include <memory.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "libqrtr.h"

#define MAX_LEN 1024

static const char* source_path;
FILE *sourcefile;
static int yyline = 1;
static int yychar = 1;
static bool end = false;

static void yyerror(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);

	fprintf(stderr, "%s:%u:%u: parse error: \n\t", source_path, yyline, yychar);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");

	va_end(ap);

	exit(1);
}

/* Skip over white space and comments (which start with '#', end with '\n') */
static bool skip(char ch)
{
	static bool in_comment = false;

	if (in_comment) {
		if (ch == '\n')
			in_comment = false;
		return true;
	}

	if (!(ch == ':' || ch == 'x' || ch == 'X') && !isxdigit(ch))
		return true;

	if (ch == '#' || ch == '<')
		in_comment = true;

	return in_comment;
}

static char input()
{
	int ch;

	ch = fgetc(sourcefile);
	if (ch < 0)
		return 0;	/* End of input */

	if (ch == '\n')
		yyline++;
	else if (!isascii(ch))
		yyerror("invalid non-ASCII character");
	else if (!ch)
		yyerror("invalid NUL character");

	yychar++;

	return (char)ch;
}

static void unput(int ch)
{
	if (ch == '\n')
		yyline--;
	if (ungetc(ch, sourcefile) != ch)
		yyerror("ungetc error");
}

static inline uint8_t to_hex(uint8_t ch)
{
	ch &= 0xf;
	return ch <= 9 ? '0' + ch : 'a' + ch - 10;
}

static uint8_t yylex()
{
	char ch;
	char buf[3];
	int len = 0, i;
	uint8_t out;

	while ((ch = input()) && skip(ch))
		;

	if (!ch) {
		end = true;
		return 0;
	}

	while (isxdigit(ch) && len < 2) {
		buf[len++] = ch;
		ch = input();
	}

	if (len & 0b1)
		yyerror("Odd number of hex digits!\n");

	if (!ch) {
		end = true;
		return 0;
	}

	if (!(ch == ':' || ch == '\n')) {
		yyerror("Expected ':' or EOL\n");
	}

	printf("Parsed: %s\n", buf);
	i = sscanf(&buf[0], "%2hhx", &out);
	if (i < 0) {
		fprintf("sscanf failed: %d (%d: %s)\n", i, errno, strerror(errno));
		end = true;
		return 0;
	}

	return out;
}

static size_t parse(uint8_t *buf)
{
	int i = 0;

	for (i = 0; i < MAX_LEN && !end; i++)
	{
		buf[i] = yylex();
	}

	return i;
}

int main(int argc, char **argv)
{
	int opt;
	struct stat sb;
	uint8_t buf[MAX_LEN];
	size_t buf_len;
	struct qmi_tlv *tlv;

	while ((opt = getopt(argc, argv, "f:")) != -1) {
		switch (opt) {
		case 'f':
			source_path = optarg;
			break;
		default:
			fprintf(stderr, "Unknown arg %c\n", opt);
			return 1;
		}
	}

	if (!source_path) {
		fprintf(stderr, "tlv_dump -f <file>\n");
		return 1;
	}

	if (!stat(source_path, &sb) == 0 || S_ISDIR(sb.st_mode)) {
		fprintf(stderr, "File %s doesn't exist!\n", source_path);
		return 1;
	}

	sourcefile = fopen(source_path, "r");
	if (!sourcefile) {
		fprintf(stderr, "Failed to open '%s' (%d: %s)\n", source_path,
			errno, strerror(errno));
		return EXIT_FAILURE;
	}

	buf_len = parse(&buf[0]);
	printf("Got %lu bytes\n", buf_len);

	tlv = qmi_tlv_decode(buf, buf_len);

	qmi_tlv_dump(tlv);

	return 0;
}
