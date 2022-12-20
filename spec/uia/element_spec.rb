require 'spec_helper'

describe Uia::Element do
  Given(:element) { wait_until { Uia.find_element(id: 'MainFormWindow') } }
  Given(:about_box) { wait_until { Uia.find_element(id: 'AboutBox') } }
  Given { element.as(:window).visual_state = :normal }

  context '#drag' do
    Given(:text_field) do
      text_field = element.find(id: 'multiLineTextField')
      text_field.send_keys ['this', :enter, 'is', :enter, 'multiple', :enter, 'lines']
      text_field
    end
    Given(:dimensions) do
      r = text_field.bounding_rectangle
      {width: r[2], height: r[3]}
    end

    When do
      text_field.drag start: [2, 2], end: [dimensions[:width], dimensions[:height]]
      text_field.send_keys :backspace
    end

    Then { expect(text_field.as(:text).text).to eq('') }
  end

  context 'properties' do
    let(:raw_element) { element.instance_variable_get(:@element) }
    Given(:about_button) { element.find name: 'About', control_type: :button }

    Then { element.handle != 0 }
    Then { element.name == 'MainFormWindow' }
    Then { element.id == 'MainFormWindow' }
    Then { about_button.help_text =~ /click about to find out/i }
    Then { element.class_name =~ /Forms.*app/i }
    Then { expect(element.find(id: 'textField')).to be_enabled }
    Then do
      expect(element.bounding_rectangle.count).to eq(4)
      expect(element.bounding_rectangle).to be_all { |e| e.instance_of? Fixnum }
    end

    context 'visibility' do
      When { element.as(:window).visual_state = :minimized }
      Then { element.visible? == false }
    end

    context 'focus' do
      Given(:text_field) { element.find(id: 'textField').as :value }

      context 'initially' do
        Then { text_field.focused? == false }
      end

      context 'explicitly' do
        When { text_field.focus }
        Then { text_field.focused? == true }
      end
    end

    context '#control_type' do
      Then { element.control_type == :window }

      context 'unknown' do
        Given { allow(raw_element).to receive(:control_type_id).and_return(777) }
        Then { element.control_type == :unknown }
      end
    end

    context '#patterns' do
      Then { expect(element.patterns).to match_array([:transform, :window]) }

      context 'unknown' do
        Given { allow(raw_element).to receive(:pattern_ids).and_return([7777]) }
        Then { expect(element.patterns).to eq([:unknown]) }
      end

      context '#as' do
        When(:cast) { element.as :toggle }
        Then { cast == Failure(UnsupportedPattern, "Pattern toggle not found in [:window, :transform]") }
      end
    end

    context '#refresh' do
      Given!(:check_box) do
        check_box = element.find(id: 'checkBox').as :toggle
        check_box.toggle_state = :off
        check_box
      end

      Given!(:label) { element.find(id: 'checkBoxLabel') }
      When { check_box.toggle_state = :on; label.refresh }
      Then { label.name == 'checkBox is on' }
    end
  end

  context '#send_keys' do
    Given(:text_field) { element.find(id: 'textField').as :value }
    When { text_field.send_keys 'abcde', [:left] * 3, ' fgh ' }
    Then { text_field.value == 'ab fgh cde' }
  end

  context '#find' do
    context 'id' do
      Then { element.find(id: 'textField') != nil }
      Then { element.find(id: 'does not exist') == nil }
    end

    context 'name, value' do
      Then { element.find(name: 'No option selected') != nil }
      Then { element.find(name: 'does not exist') == nil }
      Then { element.find(value: 'No option selected') != nil }
    end

    context 'title' do
      Then { element.find(title: /Group.*of radio/i) != nil }
    end

    context 'handle' do
      Given(:child_handle) { element.find(id: 'textField').handle }
      Then { element.find(handle: child_handle).id == 'textField' }
    end

    context 'control_type' do
      Then { element.find(control_type: :custom).id == 'automatableMonthCalendar1' }
      Then { element.find(control_type: [:semantic_zoom, :custom]).id == 'automatableMonthCalendar1' }
    end

    context 'pattern' do
      Then { element.find(pattern: :range_value).id == 'numericUpDown1' }
      Then { element.find(pattern: [:selection_item, :range_value]).id == 'numericUpDown1' }
      Then { expect { element.find(pattern: [:not_valid, :range_value]) }.to raise_error RuntimeError, /IsNotValidPatternAvailableProperty is not a valid AutomationProperty/ }
    end

    context 'combinations' do
      Then { element.find(control_type: :list, name: 'linkLabel1').id == 'FruitListBox' }
      Then { element.find(control_type: :button, name: 'Forward', scope: :children) == nil }
      Then { element.find(pattern: :invoke, name: 'About').id == 'aboutButton' }
      Then { element.find(control_type: :custom, id: 'automatableMonthCalendar1').name == 'linkLabel1' }
      Then { element.find(value: 'linkLabel1', id: 'automatableMonthCalendar1').control_type == :custom }
    end

    context 'invalid' do
      When(:bad_locator) { element.find(bad_locator: 123) }
      Then { bad_locator == Failure(BadLocator, "{:bad_locator=>123} is not a valid locator") }
    end

    context 'limiting scope' do
      Then { element.find(name: 'label2', scope: :children) == nil }
    end
  end

  context '#find_all' do
    Given(:list_box) { element.find(id: 'FruitListBox') }

    Then { list_box.find_all(control_type: :list_item).map(&:name) == ['Apple', 'Orange', 'Mango'] }
    Then { element.find_all(control_type: :tree_item, name: 'Parent Two').count == 1 }
    Then { expect { element.find_all(handle: 123) }.to raise_error BadLocator }
  end

  context '#filter' do
    context 'control_type' do
      When(:buttons) { element.filter(control_type: :radio_button) }
      Then { buttons.map(&:control_type) == [:radio_button] * 3 }
    end

    context 'pattern' do
      Then { element.filter(pattern: :value).count == 4 }
    end

    context 'combinations' do
      Then { element.filter(control_type: :button, name: 'About')[0].id == 'aboutButton' }
    end

    context 'multiple' do
      When(:radio_or_value) { element.filter(control_type: [:radio_button, :text]) }
      Then { expect(radio_or_value.count).to eq(8) }

      When(:value_or_invoke) { element.filter(pattern: [:value, :text]) }
      Then { expect(value_or_invoke.count).to eq(5) }
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
  end

  context '#children' do
    Then { element.children.count == 27 }
    Then { element.children.all? { |c| c.instance_of? Uia::Element } }
  end

  context '#descendants' do
    Then { element.descendants.count > element.children.count }
    Then { element.descendants.all? { |c| c.instance_of? Uia::Element } }
  end
end
