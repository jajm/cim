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

#define cim_typeof_first(cim_first, ...) __typeof__(cim_first)

#define cim_call_callback(cim_callback, ...) ({ \
	void *cim_ret = NULL; \
	if (!strcmp(#__VA_ARGS__, "")) { \
		void * (*cim_cb)(void) = cim_callback; \
		cim_ret = cim_cb ? cim_cb() : NULL; \
	} else { \
		void * (*cim_cb)(cim_typeof_first(__VA_ARGS__), ...) \
			= cim_callback; \
		cim_ret = cim_cb ? cim_cb(__VA_ARGS__) : NULL; \
	} \
	cim_ret; \
})

#define cim_call(cim_type, cim_callback_name, ...) \
	cim_call_callback(emb_type_get_callback(cim_type, cim_callback_name), \
		__VA_ARGS__)


#endif /* ! cim_helper_macros_h_included */
