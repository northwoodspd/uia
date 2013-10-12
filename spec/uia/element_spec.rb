require 'spec_helper'

describe Element do
  Given(:element) { find_element(id: 'MainFormWindow') }
  Given(:about_box) { find_element(id: 'AboutBox') }

  context 'properties' do
    Then { element.handle != 0 }
    Then { element.name == 'MainFormWindow' }
  end

  context '#click' do
    Given(:about) { element.children.find { |c| c.name == 'About' } }
    Given(:disabled_checkbox) { element.children.find { |c| c.name == 'checkBoxDisabled' } }

    context 'enabled elements' do
      When { about.click }
      Then { about_box != nil }
      And { about_box.children.find { |c| c.name == 'OK' }.click }
    end

    context 'disabled elements' do
      When(:click_disabled) { disabled_checkbox.click }
      Then { click_disabled.should have_failed('Target element cannot receive focus.') }
    end
  end

  context '#children' do
    Then { element.children.count == 27 }
    Then { element.children.all? { |c| c.instance_of? Element } }
  end

  context '#descendants' do
    Then { element.descendants.count > element.children.count }
    Then { element.descendants.all? { |c| c.instance_of? Element } }
  end
end
