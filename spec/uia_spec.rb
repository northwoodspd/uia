require 'spec_helper'

describe Uia do
  context '#find_element' do
    Given(:main_window) { find_element id: 'MainFormWindow' }

    context 'by id' do
      Then { find_element(id: 'MainFormWindow') != nil }
      Then { find_element(id: 'not there') == nil }
    end

    context 'by name' do
      Then { find_element(name: 'MainFormWindow') != nil }
      Then { find_element(name: 'not there') == nil }
    end

    context 'by process id' do
      Then { find_element(pid: @app.pid) != nil }
      Then { find_element(pid: -1) == nil }
    end

    context 'by runtime id' do
      Then { find_element(runtime_id: main_window.runtime_id) != nil }
      Then { find_element(runtime_id: []) == nil }

      context 'can search descendants' do
        Given(:element_with_no_handle) { find_element(id: 'MainFormWindow').find(name: 'Parent Two') }
        Then { element_with_no_handle.click.should be_true }
      end
    end

    context 'by window handle' do
      Then { find_element(handle: main_window.handle) != nil }
      Then { expect { find_element(handle: 0x0) }.to raise_error }
    end

    context 'invalid locators' do
      When(:bad_input) { find_element(bad: 123) }
      Then { bad_input.should have_failed(BadLocator, '{:bad=>123} is not a valid locator') }
    end
  end
end