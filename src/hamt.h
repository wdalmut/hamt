#ifndef _HAMT_H_
#define _HAMT_H_

struct elem_t {
    struct elem_t **leafs;
    char *content;
};

typedef struct elem_t leaf;

/**
 * Set a new key/value in the hashmap
 *
 * Just set a key/value pair in the hashmap
 *
 *     hamt_set(leafs, "key", "value");
 */
void hamt_set(leaf *, const char *, const char *);


/**
 * Get an existing key
 *
 * Retrieve an existing key
 *
 *     char *content = get(leafs, "hello");
 */
char *hamt_get(leaf *, const char *);

/**
 * Remove an existing keyd
 *
 * Try to remove an existing key
 *
 *     hamt_del(leafs, "hello");
 */
void hamt_del(leaf *, const char *);

#endif
