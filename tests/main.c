#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/hamt.h"

#include "minunit.h"

int tests_run = 0;

static char *test_add_elements() {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    hamt_set(root, "key", "walter");
    hamt_set(root, "test", "content");
    hamt_set(root, "a", "ciao");

    return 0;
}

static char *test_get_null_elements() {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    char *res = hamt_get(root, "key");

    mu_assert("Get on missing key should return a NULL value", res == '\0');
    return 0;
}

static char *test_get_an_existing_element() {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    hamt_set(root, "key", "walter");
    char *res = hamt_get(root, "key");

    mu_assert("The key should be a valid string", strcmp("walter", res) == 0);
    return 0;
}

static char *test_delete_an_existing_element() {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    hamt_set(root, "key", "walter");

    hamt_del(root, "key");

    mu_assert("The current value should be null but it is not...", NULL == hamt_get(root, "key"));
    return 0;
}

static char *test_delete_a_missing_element() {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    hamt_del(root, "key");

    mu_assert("The current value should be null but it is not...", NULL == hamt_get(root, "key"));

    return 0;
}

static char *all_tests() {
    mu_run_test(test_add_elements);
    mu_run_test(test_get_null_elements);
    mu_run_test(test_get_an_existing_element);
    mu_run_test(test_delete_an_existing_element);
    mu_run_test(test_delete_a_missing_element);
    return 0;
}

int main(void) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

