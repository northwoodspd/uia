require 'spec_helper'

describe Uia::ControlTypes::MenuItems do
  Given(:main) { Uia.find_element(title: 'MainFormWindow').with(:menu_items) }

  after(:each) do
    about = Uia.find_element(title: 'About')
    about.send_keys [:alt, :f4] if about
  end

  context '#menu_item' do
    Then { main.menu_item('non-existent') == nil }
    Then { main.menu_item('File', 'Roundabout Way', 'To', 'Not There') == nil }

    Then { main.menu_item('File').name == 'File' }
    Then { main.menu_item('File', 'Roundabout Way', 'To').name == 'To' }
  end

  context '#select_menu_item' do
    context 'valid' do
      When { main.select_menu_item 'File', 'Roundabout Way', 'To', 'About' }
      Then { Uia.find_element(title: 'About') != nil }
    end

    context 'invalid' do
      Given(:bad_path) { main.select_menu_item 'File', 'Roundabout Way', 'To', 'Something Not There' }
      Then { expect { bad_path }.to raise_error(RuntimeError, /Something Not There/) }
    end
  end
end