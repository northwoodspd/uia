# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'uia/version'

Gem::Specification.new do |spec|
  spec.name          = 'uia'
  spec.version       = Uia::VERSION
  spec.authors       = ['Levi Wilson']
  spec.email         = ['levi@leviwilson.com']
  spec.description   = %q{A low-level wrapper around Microsoft UI Automation for ruby}
  spec.summary       = %q{A low-level wrapper around Microsoft UI Automation for ruby}
  spec.homepage      = 'https://github.com/northwoodspd/uia'
  spec.license       = 'MIT'

  binaries = [
    'ext/UiaDll/Release/UiaDll.dll',
    'ext/UiaDll/Release/UIA.Helper.dll'
  ]

  exclude = lambda {|p| p =~ /(gtest)|(gmock)/i }

  spec.files         = `git ls-files`.split($/).reject(&exclude) + binaries
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']

  spec.add_runtime_dependency 'ffi', '~> 1.11.2'
  spec.add_runtime_dependency 'require_all', '~> 3.0'

  spec.add_development_dependency 'bundler', '>= 1.3'
  spec.add_development_dependency 'rake', '~> 10.5'
  spec.add_development_dependency 'rspec', '~> 3.9'
  spec.add_development_dependency 'rspec-given', '~> 3.8'
  spec.add_development_dependency 'childprocess', '~> 3.0'
  spec.add_development_dependency 'albacore', '~> 3.0.1'
end
