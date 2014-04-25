#include <limits.h>
#include <stdio.h>
#include <libtap13/tap.h>
#include <sds.h>
#include "cim.h"

int main()
{
	short **sh;
	int **i;
	long **l;
	long long **ll;
	unsigned short **ush;
	unsigned int **ui;
	unsigned long **ul;
	unsigned long long **ull;
	float **f;
	double **d;
	long double **ld;
	char **s;

	plan(99);

	/* Allocation on the stack */

	sh = Short(1);
	isnt(sh, NULL, "sh isn't null");
	isnt(*sh, NULL, "*sh isn't null either");
	is(**sh, 1, "**sh == 1");
	str_eq(emb_type_name(sh), "Short", "type of sh is \"Short\"");

	i = Int(1);
	isnt(i, NULL, "i isn't null");
	isnt(*i, NULL, "*i isn't null either");
	is(**i, 1, "**i == 1");
	str_eq(emb_type_name(i), "Int", "type of i is \"int\"");

	l = Long(1);
	isnt(l, NULL, "l isn't null");
	isnt(*l, NULL, "*l isn't null either");
	is(**l, 1, "**l == 1");
	str_eq(emb_type_name(l), "Long", "type of l is \"Long\"");

	ll = LongLong(1);
	isnt(ll, NULL, "ll isn't null");
	isnt(*ll, NULL, "*ll isn't null either");
	is(**ll, 1, "**ll == 1");
	str_eq(emb_type_name(ll), "LongLong", "type of ll is \"LongLong\"");

	ush = UShort(1);
	isnt(ush, NULL, "ush isn't null");
	isnt(*ush, NULL, "*ush isn't null either");
	is(**ush, 1, "**ush == 1");
	str_eq(emb_type_name(ush), "UShort", "type of ush is \"UShort\"");

	ui = UInt(1);
	isnt(ui, NULL, "ui isn't null");
	isnt(*ui, NULL, "*ui isn't null either");
	is(**ui, 1, "**ui == 1");
	str_eq(emb_type_name(ui), "UInt", "type of ui is \"int\"");

	ul = ULong(1);
	isnt(ul, NULL, "ul isn't null");
	isnt(*ul, NULL, "*ul isn't null either");
	is(**ul, 1, "**ul == 1");
	str_eq(emb_type_name(ul), "ULong", "type of ul is \"ULong\"");

	ull = ULongLong(1);
	isnt(ull, NULL, "ull isn't null");
	isnt(*ull, NULL, "*ull isn't null either");
	is(**ull, 1, "**ull == 1");
	str_eq(emb_type_name(ull), "ULongLong", "type of ull is \"ULongLong\"");

	f = Float(1e0);
	isnt(f, NULL, "f isn't null");
	isnt(*f, NULL, "*f isn't null either");
	is(**f, 1e0f, "**f == 1e0f");
	str_eq(emb_type_name(f), "Float", "type of f is \"Float\"");

	d = Double(1e0);
	isnt(d, NULL, "d isn't null");
	isnt(*d, NULL, "*d isn't null either");
	is(**d, 1e0, "**d == 1e0");
	str_eq(emb_type_name(d), "Double", "type of d is \"Double\"");

	ld = LongDouble(1e0);
	isnt(ld, NULL, "ld isn't null");
	isnt(*ld, NULL, "*ld isn't null either");
	is(**ld, 1e0L, "**ld == 1e0L");
	str_eq(emb_type_name(ld), "LongDouble", "type of ld is \"LongDouble\"");

	s = Str("hello");
	isnt(s, NULL, "s isn't null");
	str_eq(*s, "hello", "*s is \"hello\"");
	str_eq(emb_type_name(s), "Str", "type of s is \"string\"");


	/* Allocation on the heap */

	cim_initialize();

	sh = new(Short, (short) 1);
	isnt(sh, NULL, "sh isn't null");
	isnt(*sh, NULL, "*sh isn't null either");
	is(**sh, 1, "**sh == 1");
	str_eq(emb_type_name(sh), "Short", "type of sh is \"Short\"");
	delete(sh);

	i = new(Int, 1);
	isnt(i, NULL, "i isn't null");
	isnt(*i, NULL, "*i isn't null either");
	is(**i, 1, "**i == 1");
	str_eq(emb_type_name(i), "Int", "type of i is \"int\"");
	delete(i);

	l = new(Long, 1L);
	isnt(l, NULL, "l isn't null");
	isnt(*l, NULL, "*l isn't null either");
	is(**l, 1, "**l == 1");
	str_eq(emb_type_name(l), "Long", "type of l is \"Long\"");
	delete(l);

	ll = new(LongLong, 1LL);
	isnt(ll, NULL, "ll isn't null");
	isnt(*ll, NULL, "*ll isn't null either");
	is(**ll, 1, "**ll == 1");
	str_eq(emb_type_name(ll), "LongLong", "type of ll is \"LongLong\"");
	delete(ll);

	ush = new(UShort, (short) 1);
	isnt(ush, NULL, "ush isn't null");
	isnt(*ush, NULL, "*ush isn't null either");
	is(**ush, 1, "**ush == 1");
	str_eq(emb_type_name(ush), "UShort", "type of ush is \"UShort\"");
	delete(ush);

	ui = new(UInt, 1);
	isnt(ui, NULL, "ui isn't null");
	isnt(*ui, NULL, "*ui isn't null either");
	is(**ui, 1, "**ui == 1");
	str_eq(emb_type_name(ui), "UInt", "type of ui is \"int\"");
	delete(ui);

	ul = new(ULong, 1L);
	isnt(ul, NULL, "ul isn't null");
	isnt(*ul, NULL, "*ul isn't null either");
	is(**ul, 1, "**ul == 1");
	str_eq(emb_type_name(ul), "ULong", "type of ul is \"ULong\"");
	delete(ul);

	ull = new(ULongLong, 1LL);
	isnt(ull, NULL, "ull isn't null");
	isnt(*ull, NULL, "*ull isn't null either");
	is(**ull, 1, "**ull == 1");
	str_eq(emb_type_name(ull), "ULongLong", "type of ull is \"ULongLong\"");
	delete(ull);

	f = new(Float, 1e0f);
	isnt(f, NULL, "f isn't null");
	isnt(*f, NULL, "*f isn't null either");
	is(**f, 1e0f, "**f == 1e0f");
	str_eq(emb_type_name(f), "Float", "type of f is \"Float\"");
	delete(f);

	d = new(Double, 1e0);
	isnt(d, NULL, "d isn't null");
	isnt(*d, NULL, "*d isn't null either");
	is(**d, 1e0, "**d == 1e0");
	str_eq(emb_type_name(d), "Double", "type of d is \"Double\"");
	delete(d);

	ld = new(LongDouble, 1e0L);
	isnt(ld, NULL, "ld isn't null");
	isnt(*ld, NULL, "*ld isn't null either");
	is(**ld, 1e0L, "**ld == 1e0L");
	str_eq(emb_type_name(ld), "LongDouble", "type of ld is \"LongDouble\"");
	delete(ld);

	s = new(Str, "world");
	isnt(s, NULL, "s isn't null");
	str_eq(*s, "world", "*s is \"world\"");
	str_eq(emb_type_name(s), "Str", "type of s is \"Str\"");
	strcpy(*s, "hello");
	str_eq(*s, "hello", "*s is modifiable");
	delete(s);

	s = new(String, "world");
	isnt(s, NULL, "s isn't null");
	str_eq(*s, "world", "*s is \"world\"");
	str_eq(emb_type_name(s), "String", "type of s is \"String\"");
	*s = sdscat(*s, "!!");
	str_eq(*s, "world!!", "*s is modifiable");
	delete(s);

	return 0;
}
