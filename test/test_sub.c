#include <criterion/criterion.h>
#include "../inc/project.h"

Test(test2_suite, simple_sub_test) {
	cr_expect(sub(2, 2) == 0, "Expected \"simple_add_test\" sub(2,2) != 0 ? the difference is 0.");
	cr_expect(sub(143, 0) == 143, "Expected \"simple_add_test\" sub(143, 0) != 143 ? the difference of 143 - 0 is 143.");
	cr_expect(sub(-25, 25) == -50, "Expected \"simple_add_test\" sub(-25, 25) != 0 ? the difference of  -25 - 25 is -50");
	cr_expect(sub(0, -1) == 1, "Expected \"simple_add_test\" sub(0, -1) != 1 ? the difference of 0 - (-1) is -1");
	cr_expect(sub(0, 1) == -1, "Expected \"simple_add_test\" sub(0, 1) != 1 ? the difference of 0 - 1 is -1");
}
