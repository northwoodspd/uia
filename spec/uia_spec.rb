require 'spec_helper'

describe Uia do
  context '#children' do
    Then { Uia.children.find { |e| e.name =~ /MainFormWindow/ } != nil }
  end

  context '#find_element' do
    Given(:main_window) { Uia.find_element id: 'MainFormWindow' }

    context 'by id' do
      Then { Uia.find_element(id: 'MainFormWindow') != nil }
      Then { Uia.find_element(id: /[Mm]ain/) != nil }
      Then { Uia.find_element(id: 'not there') == nil }
    end

    context 'by name' do
      Then { Uia.find_element(name: 'MainFormWindow') != nil }
      Then { Uia.find_element(name: /[Mm]ain.*Window/ ) != nil }
      Then { Uia.find_element(name: 'not there') == nil }
    end

    context 'by process id' do
      Then { Uia.find_element(pid: @app.pid) != nil }
      Then { Uia.find_element(pid: -1) == nil }
    end

    context 'by runtime id' do
      Then { Uia.find_element(runtime_id: main_window.runtime_id) != nil }

      context 'can search descendants' do
        Given(:element_with_no_handle) { Uia.find_element(id: 'MainFormWindow').find(name: 'Parent Two') }
        Then { element_with_no_handle.click.should be_true }
      end
    end

    context 'by window handle' do
      Then { Uia.find_element(handle: main_window.handle) != nil }
      Then { expect { Uia.find_element(handle: 0x0) }.to raise_error }
    end

    context 'invalid locators' do
      When(:bad_input) { Uia.find_element(bad: 123) }
      Then { bad_input.should have_failed(Uia::BadLocator, '{:bad=>123} is not a valid locator') }
    end
  end
end