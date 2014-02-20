module RBShop
  # And +Image+ is an abstraction of any image
  # file that GraphicsMagick can load.

  class Image
    # Loads an image from a file.
    #
    # +nil+ is returned if the file is an invalid image.
    #
    #   img = Image.load('cat.jpg')
    #   # => <RBShop::Image:0x007fa15c2fb7f0>
    def self.load(path); end
  end
end