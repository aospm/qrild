/*
 * Copyright (C) 2022, Linaro Ltd.
 * Author: Caleb Connolly <caleb.connolly@linaro.org>
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

#include <string>

#include "stdlib.h"

#include "libqril_client.hh"

namespace libqril {

// Helpers defined in qrild_android_config.cc for now
// should be moved
/*
 * https://gitlab.freedesktop.org/mobile-broadband/libqmi/-/blob/main/src/qmicli/qmicli-uim.c#L999
 */
static const char bcd_chars[] = "0123456789\0\0\0\0\0\0";

std::string decode_iccid(uint8_t *bcd, uint8_t len) {
    char *str = (char *)zalloc(len * 2 + 1);
    for (size_t i = 0; i < len; i++) {
        str[i * 2] = (bcd_chars[bcd[i] & 0xF]);
        str[i * 2 + 1] = (bcd_chars[(bcd[i] >> 4) & 0xF]);
    }

    auto s = std::string(str);
    free(str);
    return s;
}

std::string decode_eid(uint8_t *eid, uint8_t len) {
    char *str = (char *)zalloc(len * 2 + 1);
    for (size_t i = 0; i < len; i++) {
        str[i * 2] = bcd_chars[(eid[i] >> 4) & 0xF];
        str[i * 2 + 1] = bcd_chars[eid[i] & 0xF];
    }

    auto s = std::string(str);
    free(str);
    return s;
}

std::string decode_bytes(uint8_t *bytes, size_t len) {
    char *str = bytes_to_hex_string(bytes, len);
    auto s = std::string(str);
    free(str);
    return s;
}

}
