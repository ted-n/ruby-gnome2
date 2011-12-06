/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2011  Ruby-GNOME2 Project Team
 *  Copyright (C) 2002,2003 Masao Mutoh
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include "rbgtk3private.h"

#define RG_TARGET_NAMESPACE cCellRendererText
#define _SELF(s) (RVAL2GTKCELLRENDERERTEXT(s))

static VALUE
rg_initialize(VALUE self)
{
    RBGTK_INITIALIZE(self, gtk_cell_renderer_text_new());
    return Qnil;
}

static VALUE
rg_set_fixed_height_from_font(VALUE self, VALUE number_of_rows)
{
    gtk_cell_renderer_text_set_fixed_height_from_font(_SELF(self), NUM2INT(number_of_rows));
    return self;
}

void
Init_gtk_cellrenderertext(VALUE mGtk)
{
    VALUE RG_TARGET_NAMESPACE = G_DEF_CLASS(GTK_TYPE_CELL_RENDERER_TEXT, "CellRendererText", mGtk);

    RG_DEF_METHOD(initialize, 0);
    RG_DEF_METHOD(set_fixed_height_from_font, 1);
    G_DEF_SETTER(RG_TARGET_NAMESPACE, "fixed_height_from_font");
}