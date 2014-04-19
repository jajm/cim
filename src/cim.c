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

static int * cim_int_new(int i)
{
	int *j;

	j = malloc(sizeof(int));
	if (!j) return NULL;

	*j = i;

	return j;
}

static double * cim_double_new(double d)
{
	double *e;

	e = malloc(sizeof(double));
	if (!e) return NULL;

	*e = d;

	return e;
}

void cim_initialize(void)
{
	emb_type_t *Int_type, *Double_type, *String_type;

	Int_type = emb_type_get("Int");
	emb_type_register_callback(Int_type, "new", cim_int_new);
	emb_type_register_callback(Int_type, "free", free);

	Double_type = emb_type_get("Double");
	emb_type_register_callback(Double_type, "new", cim_double_new);
	emb_type_register_callback(Double_type, "free", free);

	String_type = emb_type_get("String");
	emb_type_register_callback(String_type, "new", sdsnew);
	emb_type_register_callback(String_type, "free", sdsfree);
}
