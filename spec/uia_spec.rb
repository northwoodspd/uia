require 'spec_helper'

describe Uia do
  context '#find_element' do
    Given(:main_window) { find_element id: 'MainFormWindow' }

    context 'by id' do
      Then { find_element(id: 'MainFormWindow') != nil}
    end

    context 'by process id' do
      Then { find_element(pid: @app.pid) != nil }
    end

    context 'by runtime id' do
      Then { find_element(runtime_id: main_window.runtime_id) != nil }
    end

    context 'by window handle' do
      Then { find_element(handle: main_window.handle) != nil }
    end

    context 'invalid locators' do
      When(:bad_input) { find_element(bad: 123) }
      Then { bad_input.should have_failed(BadLocator, '{:bad=>123} is not a valid locator') }
    end
  end
end