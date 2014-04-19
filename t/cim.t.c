#include <libtap13/tap.h>
#include <sds.h>
#include "cim.h"

int main()
{
	int **i;
	char **s;

	plan(15);

	/* Allocation on the stack */

	i = $("Int", to_ptr(2));
	isnt(i, NULL, "i isn't null");
	isnt(*i, NULL, "*i isn't null either");
	is(**i, 2, "**i == 2");
	str_eq(emb_type_name(i), "Int", "type of i is \"int\"");

	s = $("String", "hello");
	isnt(s, NULL, "s isn't null");
	str_eq(*s, "hello", "*s is \"hello\"");
	str_eq(emb_type_name(s), "String", "type of s is \"string\"");


	/* Allocation on the heap */

	cim_initialize();

	i = new("Int", 3);
	isnt(i, NULL, "i isn't null");
	isnt(*i, NULL, "*i isn't null either");
	is(**i, 3, "**i == 3");
	str_eq(emb_type_name(i), "Int", "type of i is \"int\"");
	delete(i);

	s = new("String", "world");
	isnt(s, NULL, "s isn't null");
	str_eq(*s, "world", "*s is \"world\"");
	str_eq(emb_type_name(s), "String", "type of s is \"string\"");
	*s = sdscat(*s, "!!");
	str_eq(*s, "world!!", "*s is modifiable");
	delete(s);

	return 0;
}
