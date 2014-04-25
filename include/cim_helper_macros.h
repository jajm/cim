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

#ifndef cim_helper_macros_h_included
#define cim_helper_macros_h_included

#include <stdlib.h>
#include <string.h>
#include <embody/embody.h>

#define cim_to_ptr(type, data) \
	&((type){data})

#define cim_array_size(cim_array) \
	( sizeof(cim_array) / sizeof(*cim_array) )

#define cim_typeof_first(cim_first, ...) __typeof__(cim_first)

#define cim_call_callback_args(cim_ret_type, cim_callback, ...) ({ \
	cim_ret_type (*cim_cb)(cim_typeof_first(__VA_ARGS__), ...) \
		= cim_callback; \
	cim_cb ? cim_cb(__VA_ARGS__) : (cim_ret_type) 0; \
})

#define cim_call_callback(cim_ret_type, cim_callback, ...) ({ \
	cim_ret_type cim_ret = (cim_ret_type) 0; \
	if (!strcmp(#__VA_ARGS__, "")) { \
		cim_ret_type (*cim_cb)(void) = cim_callback; \
		cim_ret = cim_cb ? cim_cb() : (cim_ret_type) 0; \
	} else { \
		cim_ret = cim_call_callback_args(cim_ret_type, cim_callback, ##__VA_ARGS__, NULL); \
	} \
	cim_ret; \
})

#define cim_call(cim_ret_type, cim_type, cim_callback_name, ...) \
	cim_call_callback(cim_ret_type, \
		emb_type_get_callback(cim_type, cim_callback_name), \
		##__VA_ARGS__)

#define cim_vcall_callback_args(cim_callback, ...) do { \
	void (*cim_cb)(cim_typeof_first(__VA_ARGS__), ...) = cim_callback; \
	if (cim_cb) cim_cb(__VA_ARGS__); \
} while (0);

#define cim_vcall_callback(cim_callback, ...) do { \
	if (!strcmp(#__VA_ARGS__, "")) { \
		void (*cim_cb)(void) = cim_callback; \
		if (cim_cb) cim_cb(); \
	} else { \
		cim_vcall_callback_args(cim_callback, ##__VA_ARGS__, NULL); \
	} \
} while (0);

#define cim_vcall( cim_type, cim_callback_name, ...) \
	cim_vcall_callback(emb_type_get_callback(cim_type, cim_callback_name), \
		##__VA_ARGS__)


#endif /* ! cim_helper_macros_h_included */
