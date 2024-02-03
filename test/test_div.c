#include <criterion/criterion.h>
#include "../inc/project.h"

Test(test4_suite, simple_divi_test) {
	cr_expect(divi(2, 2) == 1, "Expected \"simple_divi_test\" divi(2,2) ==1");
	cr_expect(divi(25, 2) == 12, "Expected \"simple_divi_test\" divi(155, 0) == 0");
	cr_expect(divi(-25, 25) == -1, "Expected \"simple_divi_test\" divi(-25, 25) == -1");
	cr_expect(divi(100, 2) == 50, "Expected \"simple_divi_test\" divi(100, 2) == 50");
	cr_expect(divi(2, 100) == 0, "Expected \"simple_divi_test\" divi(2, 100) == 0");
}
