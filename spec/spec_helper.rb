$LOAD_PATH.unshift(File.dirname(__FILE__))
$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'lib'))

require 'rspec'
require 'rspec/given'
require 'childprocess'
require 'ffi'
require 'uia'

include Uia

def wait_until(timeout=10, &block)
  start = Time.now
  until (result = block.call) || (Time.now - start > timeout)
    sleep 0.25
  end

  raise 'Timed out' unless result
  result
end

RSpec.configure do |config|
  config.before(:all) do
    @app = ChildProcess.build('spec/app/WindowsForms.exe').start
    wait_until { Uia.find_element title: /MainFormWindow/ }
  end

  config.after(:all) do
    @app.stop unless @app.exited?
  end
end
