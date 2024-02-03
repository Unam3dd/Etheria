#include <criterion/criterion.h>
#include "../inc/project.h"

Test(test1_suite, simple_add_test) {
	cr_expect(add(2, 2) == 4, "Expected \"simple_add_test\" add(2,2) != 4 ? the sum of 2 + 2 is 4.");
	cr_expect(add(143, 0) == 143, "Expected \"simple_add_test\" add(143, 0) != 143 ? the sum of 143 + 0 is 143.");
	cr_expect(add(-25, 25) == 0, "Expected \"simple_add_test\" add(-25, 25) != 0 ? the sum of -25 + 25 is 0");
	cr_expect(add(0, -1) == -1, "Expected \"simple_add_test\" add(0, -1) != -1 ? the sum of 0 + (-1) is -1");
	cr_expect(add(0, 1) == 1, "Expected \"simple_add_test\" add(0, 1) != 1 ? the sum of 0 + 1 is 1");
}
