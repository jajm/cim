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
	&((__typeof__(data)){data})

#define snew(type_name, data) \
	emb_snew(#type_name, data)

#define $(...) snew(__VA_ARGS__)

#define new(type_name, ...) ({ \
	void *cim_new_ret = NULL; \
	void *cim_callback; \
	emb_type_t *cim_emb_type = emb_type_get(#type_name); \
	if ((cim_callback = emb_type_get_callback(cim_emb_type, "new"))) { \
		cim_new_ret = emb_container_new(cim_emb_type, \
			cim_call_callback(cim_callback, __VA_ARGS__)); \
	} \
	cim_new_ret; \
})

#define delete(ptr) \
	emb_container_free(ptr)

#define call(ptr, callback_name, ...) \
	cim_call(emb_type(ptr), callback_name, __VA_ARGS__)

#endif /* ! cim_h_included */
