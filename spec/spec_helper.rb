$LOAD_PATH.unshift(File.dirname(__FILE__))
$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'lib'))

require 'rspec'
require 'rspec/given'
require 'childprocess'
require 'ffi'
require 'uia'

include Uia

RSpec.configure do |config|
  config.before(:all) do
    @app = ChildProcess.build('spec/app/WindowsForms.exe').start
    sleep 0.5
  end

  config.after(:all) do
    @app.stop unless @app.exited?
  end
end
