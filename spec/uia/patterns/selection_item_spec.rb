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
  end

  context '#select' do
    Given(:radio) { main.find id: 'radioButton2' }

    When { radio.as(:selection_item).select }
    Then { radio_label.name == 'Option 2 selected' }
  end
end