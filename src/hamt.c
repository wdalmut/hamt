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

    leaf *current = root->leafs[(unsigned char)(*key)];

    if (!current) {
        current = (leaf *)malloc(sizeof(leaf));
        root->leafs[(int)(*key)] = current;
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

result *hamt_list(leaf *root, const char *key, result *head)
{
    leaf *current = hamt_ref(root, key);

    if (current != NULL && current->content != NULL) {
        result *k = (result *)malloc(sizeof(result));

        if (head == NULL) {
            head = k;
        } else {
            head->next = k;
        }

        char * new_key = (char *)malloc(sizeof(char)*(strlen(key)+1));
        k->key = strcpy(new_key, key);
    }

    if (current != NULL) {
        int i;
        for (i=1; i<255; i++) {
            char *extended_key = (char *)malloc(sizeof(char)*(strlen(key)+2));
            extended_key = strcpy(extended_key, key);
            extended_key[strlen(key)] = i;
            extended_key[strlen(key)+1] = '\0';

            hamt_list(root, extended_key, (head->next) ? head->next : head);

            free(extended_key);
        }
    }

    return head;
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

    leaf *current = root->leafs[(unsigned char)(*key)];

    if (!current) {
        return NULL;
    }

    currentKey +=1;
    if (!(*currentKey)) {
        return current;
    }

    return hamt_ref(current, currentKey);
}
