require 'spec_helper'

describe Uia do
  context '#find_element' do
    Given(:main_window) { find_element id: 'MainFormWindow' }

    context 'by id' do
      Then { expect(find_element(id: 'MainFormWindow')).to_not be_nil }
    end

    context 'by process id' do
      Then { expect(find_element(pid: @app.pid)).to_not be_nil }
    end

    context 'by runtime id' do
      Then { expect(find_element(runtime_id: main_window.runtime_id)).to_not be_nil }
    end

    context 'by window handle' do
      Then { expect(find_element(handle: main_window.handle)).to_not be_nil }
    end

    context 'invalid locators' do
      When(:bad_input) { find_element(bad: 123) }
      Then { bad_input.should have_failed(BadLocator, '{:bad=>123} is not a valid locator') }
    end
  end
end