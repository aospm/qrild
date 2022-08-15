#ifndef _LIST_H_
#define _LIST_H_

#include <pthread.h>
#include <memory.h>

#ifndef offsetof
#define offsetof(type, md) ((unsigned long)&((type *)0)->md)
#endif

#ifndef container_of
#define container_of(ptr, type, member)                                        \
	((type *)((char *)(ptr)-offsetof(type, member)))
#endif

// The list has a head and a tail, each list item
// has a previous and next item
struct list_head {
	union {
		struct list_head *next;
		struct list_head *head;
	};
	union {
		struct list_head *prev;
		struct list_head *tail;
	};
};

static inline void list_init(struct list_head *list)
{
	list->head = list->tail = list;
}

#define LIST_INIT(l) { &(l), &(l) }

static inline void list_append(struct list_head *list, struct list_head *item)
{
	struct list_head *tail = list->tail;

	item->next = list;
	item->prev = tail;

	tail->next = list->prev = item;
}

static inline void list_prepend(struct list_head *list, struct list_head *item)
{
	struct list_head *head = list->head;

	list->head = item;

	item->next = head;
	item->prev = list;

	head->prev = list->next = item;
}

static inline void list_remove(struct list_head *item)
{
	item->prev->next = item->next;
	item->next->prev = item->prev;
}

static inline struct list_head *list_pop(struct list_head *list)
{
	struct list_head *item;
	item = list->head;
	if (item == 0)
		return 0;
	list_remove(item);
	return item;
}

static inline struct list_head *list_last(struct list_head *list)
{
	return list->tail;
}

static inline struct list_head *list_first(struct list_head *list)
{
	return list->head;
}

static inline struct list_head *list_next(struct list_head *item)
{
	return item->next;
}

#define list_push list_append

#define list_empty(li) ((li)->head == (li)->tail)

#define list_for_each(_list, _iter)                                            \
	for (_iter = (_list)->head; (_iter) != (_list); _iter = (_iter)->next)

#define list_for_each_after(_node, _iter)                                      \
	for (_iter = (_node)->next; (_iter) != (_list); _iter = (_iter)->next)

#define list_for_each_safe(_list, _iter, _bkup)                                \
	for (_iter = (_list)->head;                                            \
	     (_iter) != (_list) && ((_bkup = (_iter)->next) || 1); _iter = (_bkup))

#define list_for_each_safe_after(_node, _iter, _bkup)                          \
	for (_iter = (_node)->next;                                            \
	     (_iter) != (_list) && ((_bkup = (_iter)->next) || 1); _iter = (_bkup))

#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define list_entry_first(list, type, member)                                   \
	container_of((list)->head, type, member)

#define list_entry_next(item, member)                                          \
	container_of((item)->member.next, typeof(*(item)), member)

#define list_for_each_entry(item, list, member)                                \
	for (item = list_entry_first(list, typeof(*(item)), member);           \
	     &item->member != list; item = list_entry_next(item, member))

#endif
