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

static char *test_set_and_get_multiple_elements() {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    hamt_set(root, "key", "walter");
    hamt_set(root, "test", "content");
    hamt_set(root, "a", "ciao");
    hamt_set(root, "a1", "ciao");


    mu_assert("The current value should not be null but it is not...", NULL != hamt_get(root, "key"));
    mu_assert("The current value should not be null but it is not...", NULL != hamt_get(root, "test"));
    mu_assert("The current value should not be null but it is not...", NULL != hamt_get(root, "a"));
    mu_assert("The current value should not be null but it is not...", NULL != hamt_get(root, "a1"));
    mu_assert("The current value should not be null but it is not...", NULL != hamt_get(root, "a"));

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

static char *test_list_from_an_existing_key() {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    hamt_set(root, "key", "value");
    result *head = hamt_list(root, "key", NULL);

    mu_assert("The 'key' should be returned", NULL != head);
    mu_assert("The key should be equals to the right value", strcmp("key", head->key) == 0);
    mu_assert("This key should not have any other elements", NULL == head->next);

    return 0;
}

static char *test_list_is_empty_on_missing_key() {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    result *head = hamt_list(root, "key", NULL);

    mu_assert("The result set should be empty for this list...", NULL == head);

    return 0;
}

static char *test_list_all_existing_keys() {
    leaf *root;

    root = (leaf *)malloc(sizeof(leaf));

    hamt_set(root, "externalkey", "value");
    hamt_set(root, "key", "value1");
    hamt_set(root, "key1", "values");
    hamt_set(root, "key11", "valuae");
    hamt_set(root, "key21", "value2");

    result *head = hamt_list(root, "key", NULL);

    mu_assert("The 'key' should be returned", NULL != head);
    mu_assert("The key should be equals to the right value", strcmp("key", head->key) == 0);
    mu_assert("This key should have other elements", NULL != head->next);
    mu_assert("The second key should be 'key1'", strcmp("key1", head->next->key) == 0);
    mu_assert("The second key should be 'key11'", strcmp("key11", head->next->next->key) == 0);
    mu_assert("The second key should be 'key21'", strcmp("key21", head->next->next->next->key) == 0);
    mu_assert("There are other elements at the end of the right list", head->next->next->next->next == 0);

    return 0;
}

static char *all_tests() {
    mu_run_test(test_add_elements);
    mu_run_test(test_get_null_elements);
    mu_run_test(test_get_an_existing_element);
    mu_run_test(test_set_and_get_multiple_elements);
    mu_run_test(test_delete_an_existing_element);
    mu_run_test(test_delete_a_missing_element);
    mu_run_test(test_list_from_an_existing_key);
    mu_run_test(test_list_is_empty_on_missing_key);
    mu_run_test(test_list_all_existing_keys);
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

