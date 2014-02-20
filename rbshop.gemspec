# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'rbshop/version'

# http://guides.rubygems.org/specification-reference/
Gem::Specification.new do |spec|
  spec.name          = "rbshop"
  spec.version       = RBShop::VERSION
  spec.authors       = ["Claire Tran"]
  spec.email         = ["CTran@fairfaxmedia.com.au"]
  spec.extensions    = ["ext/rbconf/extconf.rb"] # tells bundler to build this

  spec.description   = %q{TODO: Write a gem description}
  spec.summary       = %q{TODO: Write a gem summary}
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = `git ls-files`.split($/)
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.3"
  spec.add_development_dependency "rake"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "rspec"
end
