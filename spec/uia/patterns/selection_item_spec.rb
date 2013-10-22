require 'spec_helper'

describe Uia::Patterns::SelectionItem do
  let(:main) { find_element id: 'MainFormWindow' }
  let(:reset) { main.find(name: 'Reset').as :invoke }
  let(:radio_label) { main.find id: 'radioButtonLabel' }

  Given { reset.invoke }

  context 'properties' do
    Given(:radio) { main.find(id: 'radioButton2').as :selection_item }
    Then { expect(radio).to_not be_selected }

    context '#selected?' do
      When { radio.select }
      Then { expect(radio).to be_selected }
    end

    context '#container' do
      Given(:parent_two) { main.find(name: 'Parent Two').as :selection_item }
      Then { parent_two.container.id == 'treeView' }
    end
  end

  context '#select' do
    Given(:radio) { main.find id: 'radioButton2' }
    When { radio.as(:selection_item).select }
    Then { radio_label.name == 'Option 2 selected' }
  end

  context 'multi-select' do
    let(:toggle) { main.find(name: 'Toggle Multi-Select').as :invoke }

    def select_list
      main.find(id: 'FruitListBox').as :selection
    end

    Given(:multi_select) do
      toggle.invoke unless select_list.multi_select?
      select_list
    end
    Given(:apple) { multi_select.find(name: 'Apple').as :selection_item }

    context '#add_to_selection' do
      When { apple.add_to_selection }
      Then { expect(apple).to be_selected }
    end

    context '#remove_from_selection' do
      Given { multi_select.selection_items.each(&:add_to_selection) }
      When { apple.remove_from_selection }
      Then { expect(apple).to_not be_selected }
    end
  end
end