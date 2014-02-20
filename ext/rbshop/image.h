#include "ruby.h"

#include <wand/magick_wand.h>

void rbshop_define_image_class();

// RBShop::Image.load(path)
VALUE rbshop_img_load(VALUE klass, VALUE path); // first param is a class as this is a singleton method

// RBShop::Image#width
VALUE rbshop_img_get_width(VALUE self); //instance method, param is the instance

// RBShop::Image#height
VALUE rbshop_img_get_height(VALUE self); //instance method, param is the instance

// RBShop::Image#charcoal(radius = 0)
VALUE rbshop_img_charcoal(int argc, VALUE *argv, VALUE self); // variable number of params - argc = arg count, argv = arg values

VALUE rbshop_save(VALUE self, VALUE r_destination);

VALUE rbshop_img_blur(int argc, VALUE *argv, VALUE self);

VALUE rbshop_img_get_dimensions(VALUE self);