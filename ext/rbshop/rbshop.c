#include "ruby.h"
#include "image.h"

VALUE RBShopModule = Qnil; //Qtrue Qfalse

void
Init_rbshop() 
{
  RBShopModule = rb_define_module("RBShop");
  rbshop_define_image_class();
}