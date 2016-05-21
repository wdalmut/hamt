#include <stdio.h>
#include <stdlib.h>
#include "hamt.h"

int main(void) {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    hamt_set(root, "key", "walter");
    hamt_set(root, "test", "content");
    hamt_set(root, "a", "ciao");

    char *res = hamt_get(root, "key");

    if (res) {
        printf("%s\n", res);
    } else {
        printf("Missing key\n");
    }

    return EXIT_SUCCESS;
}
