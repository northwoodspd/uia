require 'spec_helper'

describe Uia::ControlTypes::MenuItems do
  Given(:main) { Uia.find_element(title: 'MainFormWindow').with(:menu_items) }

  after(:each) do
    about = Uia.find_element(title: 'About')
    about.send_keys [:alt, :f4] if about
  end

  context 'existence' do
    Then { expect(main).not_to have_menu_item 'non-existent' }
    Then { expect(main).not_to have_menu_item 'File', 'Roundabout Way', 'To', 'Not There' }

    Then { expect(main).to have_menu_item 'File' }
    Then { expect(main).to have_menu_item 'File', 'Roundabout Way', 'To' }
  end

  context 'selecting individually' do
    When { main.select_menu_item 'About' }
    Then { Uia.find_element(title: 'About') != nil }
  end

  context 'selecting a path' do
    context 'valid' do
      When { main.select_menu_path 'File', 'Roundabout Way', 'To', 'About' }
      Then { Uia.find_element(title: 'About') != nil }
    end

    context 'invalid' do
      Given(:bad_path) { main.select_menu_path 'File', 'Roundabout Way', 'To', 'Something Not There' }
      Then { expect { bad_path }.to raise_error(RuntimeError, /Something Not There/) }
    end
  end
end