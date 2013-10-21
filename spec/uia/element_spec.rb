require 'spec_helper'

describe Element do
  Given(:element) { find_element(id: 'MainFormWindow') }
  Given(:about_box) { find_element(id: 'AboutBox') }

  context 'properties' do
    Then { element.handle != 0 }
    Then { element.name == 'MainFormWindow' }
    Then { element.id == 'MainFormWindow' }

    context '#control_type' do
      Then { element.control_type == :window }

      context 'unknown' do
        Given { element.stub(:control_type_id).and_return(777) }
        Then { element.control_type == :unknown }
      end
    end

    context '#patterns' do
      Then { element.patterns.should =~ [:transform, :window] }

      context 'unknown' do
        Given { element.stub(:pattern_ids).and_return([7777]) }
        Then { element.patterns.should == [:unknown]}
      end
    end
  end

  context '#find' do
    context 'id' do
      Then { element.find(id: 'textField') != nil }
      Then { element.find(id: 'does not exist') == nil }
    end

    context 'name' do
      Then { element.find(name: 'No option selected') != nil }
      Then { element.find(name: 'does not exist') == nil }
    end
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
