#include <criterion/criterion.h>
#include "../inc/project.h"

Test(test3_suite, simple_mul_test) {
	cr_expect(mul(2, 2) == 4, "Expected \"simple_mul_test\" mul(2,2) != 4");
	cr_expect(mul(155, 0) == 0, "Expected \"simple_mul_test\" mul(155, 0) == 0");
	cr_expect(mul(-25, 25) == -625, "Expected \"simple_mul_test\" mul(-25, 25) == -625");
	cr_expect(mul(0, -1) == 0, "Expected \"simple_mul_test\" mul(0, -1) == 0");
	cr_expect(mul(0, 1) == 0, "Expected \"simple_mul_test\" mul(0, 1) == 0");
}
