require 'spec_helper'

describe Uia do
  context '#children' do
    Then { Uia.children.find { |e| e.name =~ /MainFormWindow/ } != nil }
  end

  context '#find_element' do
    Given(:main_window) { Uia.find_element id: 'MainFormWindow' }

    context 'by id' do
      Then { expect(Uia.find_element(id: 'MainFormWindow')).to be_instance_of(Element) }
      Then { expect(Uia.find_element(id: /[Mm]ain/)).to be_instance_of(Element) }
      Then { Uia.find_element(id: 'not there') == nil }
    end

    context 'by name / value' do
      Then { expect(Uia.find_element(name: 'MainFormWindow')).to be_instance_of(Element) }
      Then { expect(Uia.find_element(name: /[Mm]ain.*Window/)).to be_instance_of(Element) }
      Then { expect(Uia.find_element(value: /[Mm]ain.*Window/)).to be_instance_of(Element) }
      Then { Uia.find_element(name: 'not there') == nil }
    end

    context 'by process id' do
      Then { expect(Uia.find_element(pid: @app.pid)).to be_instance_of(Element) }
      Then { Uia.find_element(pid: -1) == nil }
    end

    context 'by runtime id' do
      Then { expect(Uia.find_element(runtime_id: main_window.runtime_id)).to be_instance_of(Element) }

      context 'can search descendants' do
        Given(:element_with_no_handle) { Uia.find_element(id: 'MainFormWindow').find(name: 'Parent Two') }
        Then { expect(element_with_no_handle.click).to be true }
      end
    end

    context 'by window handle' do
      Then { expect(Uia.find_element(handle: main_window.handle)).to be_instance_of(Element) }
      Then { expect { Uia.find_element(handle: 0x0) }.to raise_error(RuntimeError, /hwnd cannot be IntPtr.Zero or null/) }
    end

    context 'by title' do
      Then { expect(Uia.find_element(title: 'MainFormWindow')).to be_instance_of(Element) }
      Then { expect(Uia.find_element(title: /Main[Ff]orm/)).to be_instance_of(Element) }
      Then { Uia.find_element(title: 'probably will not find') == nil }
    end

    context 'invalid locators' do
      When(:bad_input) { Uia.find_element(bad: 123) }
      Then { bad_input == Failure(Uia::BadLocator, '{:bad=>123} is not a valid locator') }
    end
  end
end
