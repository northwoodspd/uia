$LOAD_PATH.unshift(File.dirname(__FILE__))
$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'lib'))

require 'rspec'
require 'rspec/given'
require 'childprocess'
require 'uia'

include Uia

Given.source_caching_disabled = true
Given.use_natural_assertions

RSpec.configure do |config|
  config.before(:all) do
    @app = ChildProcess.build('spec/app/WindowsForms.exe').start
    sleep 0.5
  end

  config.after(:all) do
    @app.stop unless @app.exited?
  end
end
