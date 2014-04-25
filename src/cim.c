/*
 * Copyright 2014 Julian Maurice
 *
 * This file is part of cim
 *
 * cim is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cim.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <embody/embody.h>
#include <sds.h>
#include <libgends/slist.h>
#include <libgends/dlist.h>
#include <libgends/hash_map.h>
#include <libgends/hash_map_fast.h>
#include <libgends/iterator.h>
#include "cim.h"

#define cim_new_func(type_name, type) \
	static type * cim_##type_name##_new(type data) \
	{ \
		type *data_ptr; \
		data_ptr = malloc(sizeof(type)); \
		if (!data_ptr) return NULL; \
		*data_ptr = data; \
		return data_ptr; \
	}

cim_new_func(Short, short)
cim_new_func(Int, int)
cim_new_func(Long, long)
cim_new_func(LongLong, long long)
cim_new_func(UShort, unsigned short)
cim_new_func(UInt, unsigned int)
cim_new_func(ULong, unsigned long)
cim_new_func(ULongLong, unsigned long long)

cim_new_func(Float, float)
cim_new_func(Double, double)
cim_new_func(LongDouble, long double)

#define cim_to_longlong_func(type_name, type) \
	static long long cim_##type_name##_to_longlong(type *data) \
	{ \
		return (long long) (*data); \
	}

cim_to_longlong_func(Short, short)
cim_to_longlong_func(Int, int)
cim_to_longlong_func(Long, long)
cim_to_longlong_func(LongLong, long long)
cim_to_longlong_func(UShort, unsigned short)
cim_to_longlong_func(UInt, unsigned int)
cim_to_longlong_func(ULong, unsigned long)
cim_to_longlong_func(ULongLong, unsigned long long)

cim_to_longlong_func(Float, float)
cim_to_longlong_func(Double, double)
cim_to_longlong_func(LongDouble, long double)

#define cim_to_longdouble_func(type_name, type) \
	static long double cim_##type_name##_to_longdouble(type *data) \
	{ \
		return (long double) (*data); \
	}

cim_to_longdouble_func(Short, short)
cim_to_longdouble_func(Int, int)
cim_to_longdouble_func(Long, long)
cim_to_longdouble_func(LongLong, long long)
cim_to_longdouble_func(UShort, unsigned short)
cim_to_longdouble_func(UInt, unsigned int)
cim_to_longdouble_func(ULong, unsigned long)
cim_to_longdouble_func(ULongLong, unsigned long long)

cim_to_longdouble_func(Float, float)
cim_to_longdouble_func(Double, double)
cim_to_longdouble_func(LongDouble, long double)

static char * cim_strdup(const char *s)
{
	char *str;

	str = malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(str, s);

	return str;
}

static char * cim_sds_to_str(sds s)
{
	char *str;

	str = malloc(sizeof(char) * (sdslen(s) + 1));
	strcpy(str, s);

	return str;
}

static gds_slist_t * cim_gds_slist_new(void)
{
	gds_slist_t *slist;

	slist = gds_slist_new(emb_container_free);

	return slist;
}

static gds_slist_t * cim_gds_slist_new_from_array(size_t size, void *data[])
{
	gds_slist_t *slist;

	slist = gds_slist_new_from_array(emb_container_free, size, data);

	return slist;
}

static void * cim_gds_slist_get(gds_slist_t *slist, void *key)
{
	return gds_slist_get(slist, to_uint(key));
}

#define cim_define_type(type_name) \
	type_name##_type = emb_type_get(#type_name); \
	emb_type_register_callback(type_name##_type, "new", cim_##type_name##_new); \
	emb_type_register_callback(type_name##_type, "to_longlong", cim_##type_name##_to_longlong); \
	emb_type_register_callback(type_name##_type, "to_longdouble", cim_##type_name##_to_longdouble); \
	emb_type_register_callback(type_name##_type, "free", free)

void cim_initialize(void)
{
	emb_type_t *Short_type, *Int_type, *Long_type, *LongLong_type,
		*UShort_type, *UInt_type, *ULong_type, *ULongLong_type,
		*Float_type, *Double_type, *LongDouble_type,
		*Str_type, *String_type,
		*GdsSlist_type;

	cim_define_type(Short);
	cim_define_type(Int);
	cim_define_type(Long);
	cim_define_type(LongLong);
	cim_define_type(UShort);
	cim_define_type(UInt);
	cim_define_type(ULong);
	cim_define_type(ULongLong);

	cim_define_type(Float);
	cim_define_type(Double);
	cim_define_type(LongDouble);

	Str_type = emb_type_get("Str");
	emb_type_register_callback(Str_type, "new", cim_strdup);
	emb_type_register_callback(Str_type, "free", free);
	emb_type_register_callback(Str_type, "to_str", cim_strdup);

	String_type = emb_type_get("String");
	emb_type_register_callback(String_type, "new", sdsnew);
	emb_type_register_callback(String_type, "free", sdsfree);
	emb_type_register_callback(String_type, "to_str", cim_sds_to_str);

	GdsSlist_type = emb_type_get("GdsSlist");
	emb_type_register_callback(GdsSlist_type, "new", cim_gds_slist_new);
	emb_type_register_callback(GdsSlist_type, "new_from_array",
		cim_gds_slist_new_from_array);
	emb_type_register_callback(GdsSlist_type, "push", gds_slist_push_array);
	emb_type_register_callback(GdsSlist_type, "unshift", gds_slist_unshift_array);
	emb_type_register_callback(GdsSlist_type, "pop", gds_slist_pop);
	emb_type_register_callback(GdsSlist_type, "shift", gds_slist_shift);
	emb_type_register_callback(GdsSlist_type, "size", gds_slist_size);
	emb_type_register_callback(GdsSlist_type, "get", cim_gds_slist_get);
	emb_type_register_callback(GdsSlist_type, "free", gds_slist_free);
}
