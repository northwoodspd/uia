require_relative '../../spec_helper'

describe Uia::ControlTypes::ComboBox do
  let(:main) { Uia.find_element(id: 'MainFormWindow') }
  Given(:combo_box) { main.find(id: 'FruitsComboBox').as(:value).with(:combo_box) }

  context '#items' do
    Then { combo_box.items.map(&:name) == ['Apple', 'Caimito', 'Coconut', 'Orange', 'Passion Fruit'] }
  end

  context '#set' do
    context 'by index' do
      When { combo_box.set 1 }
      Then { combo_box.value == 'Caimito' }
    end
    context 'by value' do
      When { combo_box.set 'Orange' }
      Then { combo_box.value == 'Orange' }
    end
  end
end