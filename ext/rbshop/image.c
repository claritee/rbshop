#include "image.h"

#define VARIABLE_PARAMETERS -1

// function that retuns a pointer to a wand
MagickWand *
rbshop_img_get(VALUE obj)
{
  MagickWand *wand;

  // convert Ruby object to C type
  Data_Get_Struct(
    obj,     //ruby object
    MagickWand, //C type
    wand     //where do I set it?
  );
  return wand;
}

void 
rbshop_img_free(MagickWand *wand)
{
  DestroyMagickWand(wand);
}

VALUE RBShopImageClass = Qnil; //var that will hold the image class
extern VALUE RBShopModule; //reference this


void
rbshop_define_image_class()
{
  RBShopImageClass = rb_define_class_under(
    RBShopModule, //module name
    "Image", //method name
    rb_cObject //obj type
  );

  // RBShop::Image.load(path)
  rb_define_singleton_method(
    RBShopImageClass,
    "load",
    rbshop_img_load,
    1 //no. of parameters that this method takes
  );

  // RBShop::Image#width
  rb_define_method(
    RBShopImageClass,
    "width",
    rbshop_img_get_width,
    0
  );

  // RBShop::Image#height
  rb_define_method(
    RBShopImageClass,
    "height",
    rbshop_img_get_height,
    0
  );

  // RBShop::Image#charcoal
  rb_define_method(
    RBShopImageClass,
    "charcoal",
    rbshop_img_charcoal,
    VARIABLE_PARAMETERS //-1 indicates variable number of params
  );

  // RBShop::Image#blur
  rb_define_method(
    RBShopImageClass,
    "blur",
    rbshop_img_blur,
    VARIABLE_PARAMETERS //-1 indicates variable number of params
  );

  // RBShop::Image#save
  rb_define_method(
    RBShopImageClass,
    "save",
    rbshop_save,
    1
  );

  // RBShop::Image#dimensions - return a Hash instead of self
  rb_define_method(
    RBShopImageClass,
    "dimensions",
    rbshop_img_get_dimensions,
    0
  );
}

// RBShop::Image.load(path)
VALUE
rbshop_img_load(VALUE klass, VALUE r_path)
{
  MagickWand *wand;
  wand = NewMagickWand();

  char *path = StringValueCStr(r_path); // path is a Ruby object - convert the path into a C string
  if (!MagickReadImage(wand, path))
  {
    return Qnil;
  }

  //create Ruby object and wraps a C struct into Ruby class
  VALUE self = Data_Wrap_Struct(
    RBShopImageClass,   //ruby class type
    0,           //mark function (not needed)
    rbshop_img_free,  //ruby calls this to free up memory
    wand        //what ruby is wrapping. what will ruby include in this object
  );

  return self;
}

// RBShop::Image#width
VALUE
rbshop_img_get_width(VALUE self)
{
  MagickWand *wand;

  // convert Ruby object to C type
  Data_Get_Struct(
    self,     //ruby object
    MagickWand, //C type
    wand     //where do I set it?
  );

  // get width, unsigned long number returned from ImageMagick
  unsigned long width = MagickGetImageWidth(wand);
  return INT2NUM(width);
}

VALUE rbshop_img_get_height(VALUE self)
{
  MagickWand *wand = rbshop_img_get(self);

  unsigned long height = MagickGetImageHeight(wand);
  return INT2NUM(height);
}

VALUE
rbshop_img_charcoal(int argc, VALUE *argv, VALUE self)
{
  MagickWand *wand = rbshop_img_get(self);

  VALUE r_radius;
  VALUE r_sigma;
  rb_scan_args(
    argc,    //count
    argv,    //values
    "02",    //0 required arguments, 2 optional,
    &r_radius,  //variables where arguments go into. & => address of the variable
    &r_sigma
  );

  // translate Ruby objects to C
  double radius = 0;
  double sigma = 0; // should always be initialised, otherwise this can point to garbage

  //check if object is nil, truthy check
  if(RTEST(r_radius)) { //Ruby helper
    Check_Type(r_radius, T_FLOAT); //Ruby helper. Check ruby type for this object. Raises exception if not the correct type.  Only checks one type FIXNUM or FLOAT
    radius = NUM2DBL(r_radius);
  } else {
    radius = 1;
  }

  if(RTEST(r_sigma)) {
    Check_Type(r_sigma, T_FLOAT);
    sigma = NUM2DBL(r_sigma);
  } else {
    sigma = radius / 2;
  }

  MagickCharcoalImage(wand, radius, sigma);
  return self;
}

VALUE
rbshop_img_blur(int argc, VALUE *argv, VALUE self)
{
  MagickWand *wand = rbshop_img_get(self);

  VALUE r_radius;
  VALUE r_sigma;
  rb_scan_args(
    argc,    //count
    argv,    //values
    "02",    //0 required arguments, 2 optional,
    &r_radius,  //variables where arguments go into. & => address of the variable
    &r_sigma
  );

  // translate Ruby objects to C
  double radius = 0;
  double sigma = 0; // should always be initialised, otherwise this can point to garbage

  //check if object is nil, truthy check
  if(RTEST(r_radius)) { //Ruby helper
    Check_Type(r_radius, T_FLOAT); //Ruby helper. Check ruby type for this object. Raises exception if not the correct type.  Only checks one type FIXNUM or FLOAT
    radius = NUM2DBL(r_radius);
  } else {
    radius = 1;
  }

  if(RTEST(r_sigma)) {
    Check_Type(r_sigma, T_FLOAT);
    sigma = NUM2DBL(r_sigma);
  } else {
    sigma = radius / 2;
  }

  MagickBlurImage(wand, radius, sigma);
  return self;
}

VALUE rbshop_save(VALUE self, VALUE r_destination)
{
  MagickWand *wand = rbshop_img_get(self);

  char *destination = StringValueCStr(r_destination);
  MagickWriteImage(wand, destination);

  return self;
}

VALUE
rbshop_img_get_dimensions(VALUE self)
{
  MagickWand *wand = rbshop_img_get(self);
  unsigned long width = MagickGetImageWidth(wand);
  unsigned long height = MagickGetImageHeight(wand);

  VALUE hash = rb_hash_new();
  rb_hash_aset(
    hash,
    ID2SYM(rb_intern("width")), //key
    INT2NUM(width)
  );
  rb_hash_aset(
    hash,
    ID2SYM(rb_intern("height")), //key
    INT2NUM(height)
  );
  return hash;
}
