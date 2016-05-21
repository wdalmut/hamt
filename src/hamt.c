#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "hamt.h"

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
        return current->content;
    }


    return hamt_get(current, currentKey);
}
