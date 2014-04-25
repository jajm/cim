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

#ifndef cim_h_included
#define cim_h_included

#include <embody/embody.h>
#include "cim_helper_macros.h"

void cim_initialize(void);

#define to_ptr(data) \
	cim_to_ptr(__typeof__(data), data)

#define snew(type_name, data) \
	emb_snew(#type_name, data)

#define Short(data)     snew(Short,     cim_to_ptr(short, data))
#define Int(data)       snew(Int,       cim_to_ptr(int, data))
#define Long(data)      snew(Long,      cim_to_ptr(long, data))
#define LongLong(data)  snew(LongLong,  cim_to_ptr(long long, data))
#define UShort(data)    snew(UShort,    cim_to_ptr(unsigned short, data))
#define UInt(data)      snew(UInt,      cim_to_ptr(unsigned int, data))
#define ULong(data)     snew(ULong,     cim_to_ptr(unsigned long, data))
#define ULongLong(data) snew(ULongLong, cim_to_ptr(unsigned long long, data))

#define Float(data)      snew(Float,      cim_to_ptr(float, data))
#define Double(data)     snew(Double,     cim_to_ptr(double, data))
#define LongDouble(data) snew(LongDouble, cim_to_ptr(long double, data))

#define Str(data) snew(Str, data)

#define new(type_name, ...) ({ \
	void *cim_new_ret = NULL; \
	void *cim_callback; \
	emb_type_t *cim_emb_type = emb_type_get(#type_name); \
	if ((cim_callback = emb_type_get_callback(cim_emb_type, "new"))) { \
		cim_new_ret = emb_container_new(cim_emb_type, \
			cim_call_callback(void *, cim_callback, ##__VA_ARGS__)); \
	} \
	cim_new_ret; \
})

#define new_from_array(type_name, ...) ({ \
	void *cim_new_ret = NULL; \
	void *cim_callback; \
	void *cim_args[] = {__VA_ARGS__}; \
	emb_type_t *cim_emb_type = emb_type_get(#type_name); \
	if ((cim_callback = emb_type_get_callback(cim_emb_type, "new_from_array"))) { \
		cim_new_ret = emb_container_new(cim_emb_type, \
			cim_call_callback(void *, cim_callback, \
				cim_array_size(cim_args), cim_args)); \
	} \
	cim_new_ret; \
})

#define delete(ptr) \
	emb_container_free(ptr)

#define call(cim_ret_type, cim_ptr, cim_callback_name, ...) \
	cim_call(cim_ret_type, emb_type(cim_ptr), cim_callback_name, ##__VA_ARGS__)

#define vcall(cim_ptr, cim_callback_name, ...) \
	cim_vcall(emb_type(cim_ptr), cim_callback_name, ##__VA_ARGS__)

#define to_str(ptr) \
	call(char *, ptr, "to_str", *((void **)ptr))

#define to_longlong(ptr) \
	call(long long, ptr, "to_longlong", *((void **)ptr))

#define to_long(ptr) ((long) to_longlong(ptr))
#define to_int(ptr) ((int) to_longlong(ptr))
#define to_short(ptr) ((short) to_longlong(ptr))

#define to_ulonglong(ptr) ((unsigned long long) to_longlong(ptr))
#define to_ulong(ptr) ((unsigned long) to_longlong(ptr))
#define to_uint(ptr) ((unsigned int) to_longlong(ptr))
#define to_ushort(ptr) ((unsigned short) to_longlong(ptr))

#define to_longdouble(ptr) \
	call(long double, ptr, "to_longdouble", *((void **)ptr))
#define to_double(ptr) ((double) to_longdouble(ptr))
#define to_float(ptr) ((float) to_longdouble(ptr))

#define size(ptr) \
	call(unsigned long int, ptr, "size", *ptr)

#define push(ptr, ...) ({ \
	void *cim_args[] = {__VA_ARGS__}; \
	vcall(ptr, "push", *(void**)ptr, cim_array_size(cim_args), cim_args); \
})

#define unshift(ptr, ...) ({ \
	void *cim_args[] = {__VA_ARGS__}; \
	vcall(ptr, "unshift", *(void**)ptr, cim_array_size(cim_args), cim_args); \
})

#define pop(ptr) \
	call(void *, ptr, "pop", *ptr)

#define shift(ptr) \
	call(void *, ptr, "shift", *ptr)

#define get(ptr, key) \
	call(void *, ptr, "get", *ptr, key)

#endif /* ! cim_h_included */
