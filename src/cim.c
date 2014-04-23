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

#define cim_define_type(type_name) \
	type_name##_type = emb_type_get(#type_name); \
	emb_type_register_callback(type_name##_type, "new", cim_##type_name##_new); \
	emb_type_register_callback(type_name##_type, "free", free)

void cim_initialize(void)
{
	emb_type_t *Short_type, *Int_type, *Long_type, *LongLong_type,
		*UShort_type, *UInt_type, *ULong_type, *ULongLong_type,
		*Float_type, *Double_type, *LongDouble_type,
		*String_type;

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

	String_type = emb_type_get("String");
	emb_type_register_callback(String_type, "new", sdsnew);
	emb_type_register_callback(String_type, "free", sdsfree);
}
