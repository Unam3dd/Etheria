#include "bytebreacher.h"
#include <criterion/criterion.h>
#include <string.h>

Test(test_bytebreacher_version, test_version) {
	cr_expect(strcmp(__BYTEBREACHER_VERSION__,"undefined") == 0, "Expected \"test_version\" version is !");
}
