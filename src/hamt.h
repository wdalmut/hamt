#ifndef _HAMT_H_
#define _HAMT_H_

struct elem_t {
    struct elem_t **leafs;
    char *content;
};

typedef struct elem_t leaf;

void hamt_set(leaf *, const char *, const char *);


/**
 * Get an existing key
 *
 * Retrieve an existing key
 *
 *     char *content = get(leafs, "hello");
 */
char *hamt_get(leaf *, const char *);

#endif
