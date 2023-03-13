#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "dstring/dstring.h"


string* test_string = NULL;

void setup() {
    test_string = string_new();
}

void teardown() {
    string_destroy(test_string);
    cr_expect(test_string == NULL);
}

TestSuite(basic, .init = setup, .fini = teardown);

Test(basic, always_pass) {
    cr_assert(1, "Something is really wrong here! Failed 'cr_assert(1)'.");
}

Test(basic, allocation) {
    cr_expect(ne(ptr, test_string, NULL), "Memory allocation in 'string_new()' failed.");
}

