require 'spec_helper'

describe Uia::Patterns::Toggle do
  let(:main) { Uia.find_element id: 'MainFormWindow' }
  let(:label) { main.find id: 'checkBoxLabel' }

  Given(:check_box) { main.find(id: 'checkBox').as :toggle }

  context 'properties' do
    When { check_box.toggle }

    Then { check_box.toggle_state == :on }
    Then { check_box.toggle_state == :off }
  end

  context 'toggle' do
    When { check_box.toggle }
    Then { label.name == 'checkBox is on' }
  end
end
