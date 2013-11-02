require 'spec_helper'

describe Uia::Patterns::RangeValue do
  Given(:range_value) { Uia.find_element(id: /MainForm/).find(id: 'numericUpDown1').as :range_value }

  context 'properties' do
    Then { range_value.value == 0.0 }
    Then { range_value.minimum == 0.0 }
    Then { range_value.maximum == 100.0 }
    Then { range_value.small_change == 1.0 }
    Then { range_value.large_change == 0.0 }
  end

  context '#value=' do
    When { range_value.value = 37.3 }
    Then { range_value.value == 37.3 }
  end
end