/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2011  Ruby-GNOME2 Project Team
 *  Copyright (C) 2002-2005 Masao Mutoh
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

#define RG_TARGET_NAMESPACE cImage
#define _SELF(s) (RVAL2GTKIMAGE(s))

static VALUE
rg_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE arg1, arg2;
    GType gtype;
    GtkWidget* widget = NULL;

    rb_scan_args(argc, argv, "02", &arg1, &arg2);

    if (NIL_P(arg1)){
        widget = gtk_image_new();
    } else if (TYPE(arg1) == T_STRING && argc == 1){
        widget = gtk_image_new_from_file(RVAL2CSTR(arg1));
    } else if (TYPE(arg1) == T_SYMBOL){
        widget = gtk_image_new_from_stock(rb_id2name(SYM2ID(arg1)), 
                                          RVAL2GTKICONSIZE(arg2));
    } else if (TYPE(arg1) == T_STRING){
        widget = gtk_image_new_from_icon_name(RVAL2CSTR(arg1),
                                              RVAL2GTKICONSIZE(arg2));
    } else {
        gtype = RVAL2GTYPE(arg1);
/* deprecated
        if (gtype == GDK_TYPE_IMAGE){
            widget = gtk_image_new_from_image(RVAL2GDKIMAGE(arg1),
                                              RVAL2GDKBITMAP(arg2));
        } else */if (gtype == GDK_TYPE_PIXBUF){
            widget = gtk_image_new_from_pixbuf(RVAL2GDKPIXBUF(arg1));
/* deprecated
        } else if (gtype == GDK_TYPE_PIXMAP){
            widget = gtk_image_new_from_pixmap(RVAL2GDKPIXMAP(arg1),
                                               RVAL2GDKBITMAP(arg2));
*/
        } else if (gtype == GTK_TYPE_ICON_SET){
            widget = gtk_image_new_from_icon_set(RVAL2GTKICONSET(arg1), RVAL2GTKICONSIZE(arg2));
        } else if (g_type_is_a(gtype, GDK_TYPE_PIXBUF_ANIMATION)) {
            widget = gtk_image_new_from_animation(RVAL2GDKPIXBUFANIMATION(arg1));
        }
    }
    RBGTK_INITIALIZE(self, widget);
    return Qnil;
}

static VALUE
rg_set(int argc, VALUE *argv, VALUE self)
{
    VALUE arg1, arg2;
    GType gtype;

    rb_scan_args(argc, argv, "11", &arg1, &arg2);

    if (TYPE(arg1) == T_STRING && argc == 1){
        gtk_image_set_from_file(_SELF(self), RVAL2CSTR(arg1));
    } else if (TYPE(arg1) == T_SYMBOL){
        gtk_image_set_from_stock(_SELF(self), rb_id2name(SYM2ID(arg1)), 
                                 RVAL2GTKICONSIZE(arg2));
    } else if (TYPE(arg1) == T_STRING){
        gtk_image_set_from_icon_name(_SELF(self), RVAL2CSTR(arg1),
                                     RVAL2GTKICONSIZE(arg2));
    } else {
        gtype = RVAL2GTYPE(arg1);
/* deprecated
        if (gtype == GDK_TYPE_IMAGE){
            gtk_image_set_from_image(_SELF(self), RVAL2GDKIMAGE(arg1),
                                     RVAL2GDKBITMAP(arg2));
        } else */if (gtype == GDK_TYPE_PIXBUF){
            gtk_image_set_from_pixbuf(_SELF(self), RVAL2GDKPIXBUF(arg1));

/* deprecated
        } else if (gtype == GDK_TYPE_PIXMAP){
            gtk_image_set_from_pixmap(_SELF(self), RVAL2GDKPIXMAP(arg1),
                                      RVAL2GDKBITMAP(arg2));
*/
        } else if (gtype == GTK_TYPE_ICON_SET){
            gtk_image_set_from_icon_set(_SELF(self), 
                                        RVAL2GTKICONSET(arg1), 
                                        RVAL2GTKICONSIZE(arg2));
        } else if (g_type_is_a(gtype, GDK_TYPE_PIXBUF_ANIMATION)) {
            gtk_image_set_from_animation(_SELF(self), RVAL2GDKPIXBUFANIMATION(arg1));
        } else {
            rb_raise(rb_eArgError, "invalid argument: %s", rb_class2name(arg1));
        }
    }

    return self;
}

static VALUE
rg_clear(VALUE self)
{
    gtk_image_clear(_SELF(self));
    return self;
}

void 
Init_gtk_image(VALUE mGtk)
{
    VALUE RG_TARGET_NAMESPACE = G_DEF_CLASS(GTK_TYPE_IMAGE, "Image", mGtk);
    RG_DEF_METHOD(initialize, -1);
    RG_DEF_METHOD(set, -1);
    RG_DEF_METHOD(clear, 0);

    G_DEF_CLASS(GTK_TYPE_IMAGE_TYPE, "Type", RG_TARGET_NAMESPACE);

    G_SET_SYMBOL_PROPERTY(GTK_TYPE_IMAGE, "stock");
}