# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'uia/version'

Gem::Specification.new do |spec|
  spec.name          = "Uia"
  spec.version       = Uia::VERSION
  spec.authors       = ["Levi Wilson"]
  spec.email         = ["levi@leviwilson.com"]
  spec.description   = %q{This wraps UIA stuff}
  spec.summary       = %q{This wraps UIA stuff}
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = `git ls-files`.split($/) + ['ext/UiaDll/Release/UiaDll.dll']
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_runtime_dependency 'ffi'

  spec.add_development_dependency "bundler", "~> 1.3"
  spec.add_development_dependency "rake"
end
