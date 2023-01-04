require_relative '../../spec_helper'

describe Uia::ControlTypes::ComboBox do
  let(:main) { Uia.find_element(id: 'MainFormWindow') }
  Given(:combo_box) { main.find(id: 'FruitsComboBox').with(:combo_box) }

  context '#items' do
    Then { combo_box.items.map(&:name) == ['Apple', 'Caimito', 'Coconut', 'Orange', 'Passion Fruit'] }
  end
end