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
    'ext/UiaDll/Release/UIA.Helper.dll',
    'ext/UiaDll/x64/Release x64/UiaDll.dll',
    'ext/UiaDll/x64/Release x64/UIA.Helper.dll'
  ]

  exclude = lambda {|p| p =~ /(gtest)|(gmock)/i }

  spec.files         = `git ls-files`.split($/).reject(&exclude) + binaries
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']

  spec.add_runtime_dependency 'ffi', '~> 1.9.4'
  spec.add_runtime_dependency 'require_all'

  spec.add_development_dependency 'bundler', '~> 1.3'
  spec.add_development_dependency 'rake'
  spec.add_development_dependency 'rspec', '~> 2.9'
  spec.add_development_dependency 'rspec-given'
  spec.add_development_dependency 'childprocess'
  spec.add_development_dependency 'albacore', '~> 2.2'
end
