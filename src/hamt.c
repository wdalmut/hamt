#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "hamt.h"

static leaf *hamt_ref(leaf *, const char *);

void hamt_set(leaf *root, const char *key, const char *content) {
    const char *currentKey = key;

    if (!root->leafs) {
        root->leafs = (leaf **)malloc(256 * sizeof(leaf *));
    }

    uint8_t part = key[(int)(*key)];
    leaf *current = root->leafs[part];

    if (!current) {
        current = (leaf *)malloc(sizeof(leaf));
        root->leafs[part] = current;
    }

    currentKey += 1;
    if (!(*currentKey)) {
        current->content = (char *)malloc((1+strlen(content))*sizeof(char));
        strcpy(current->content, content);
        return;
    }

    hamt_set(current, currentKey, content);
}

char *hamt_get(leaf *root, const char *key) {
    leaf * current = hamt_ref(root, key);

    if (current) {
        return current->content;
    } else {
        return NULL;
    }
}

void hamt_del(leaf *root, const char *key) {
    leaf *current = hamt_ref(root, key);

    if (current) {
        free(current->content);
        current->content = NULL;
    }
}

/**
 * Private method to look for objects
 */
static leaf *hamt_ref(leaf *root, const char *key)
{
    const char *currentKey = key;

    if (!root->leafs) {
        return NULL;
    }

    uint8_t part = key[(int)(*key)];
    leaf *current = root->leafs[part];

    if (!current) {
        return NULL;
    }

    currentKey +=1;
    if (!(*currentKey)) {
        return current;
    }

    return hamt_ref(current, currentKey);
}
