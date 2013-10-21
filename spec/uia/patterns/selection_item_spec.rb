require 'spec_helper'

describe Uia::Patterns::SelectionItem do
  let(:main) { find_element id: 'MainFormWindow' }
  let(:radio_label) { main.find id: 'radioButtonLabel' }

  context '#select' do
    Given(:radio) { main.find id: 'radioButton2' }

    When { radio.as(:selection_item).select }
    Then { radio_label.name == 'Option 2 selected' }
  end
end