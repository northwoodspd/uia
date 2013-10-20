require 'spec_helper'

describe Uia::Patterns::Value do
  Given(:text_field) do
    find_element(id: 'MainFormWindow').children.find { |e| e.id == 'textField' }
  end

  context 'properties' do
    Given(:value_field) { text_field.as(:value) }

    Then { expect(value_field).to_not be_read_only }

    When { value_field.value = 'Expected value' }
    Then { value_field.value == 'Expected value' }
  end
end
