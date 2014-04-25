#include <libtap13/tap.h>
#include <sds.h>
#include <libgends/slist.h>
#include <float.h>
#include <math.h>
#include "cim.h"

int main()
{
	gds_slist_t **slist;
	void *ptr;
	char *s;

	cim_initialize();

	plan(8);

	slist = new_from_array(GdsSlist, new(String, "foo"), new(Int, 3));
	is(size(slist), 2, "size of slist is 2");

	push(slist, new(Double, 4.2));
	is(size(slist), 3, "size of slist is 3");

	ptr = pop(slist);
	is(size(slist), 2, "size of slist is 2");
	ok(fabs(to_double(ptr) - 4.2) < DBL_EPSILON, "popped element is 4.2");
	delete(ptr);

	ptr = shift(slist);
	is(size(slist), 1, "size of slist is 1");
	s = to_str(ptr);
	if (s) {
		str_eq(s, "foo", "shifted element is \"foo\"");
		free(s);
	}
	delete(ptr);

	unshift(slist, new(Int, 1), new(Int, 2));
	is(size(slist), 3, "size of slist is 3");
	ptr = get(slist, Int(1));
	is(to_int(ptr), 2, "2nd element of slist is 2");

	delete(slist);

	return 0;
}
