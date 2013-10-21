require 'spec_helper'

describe Uia::Patterns::Toggle do
  let(:main) { find_element id: 'MainFormWindow' }
  let(:label) { main.find id: 'checkBoxLabel' }

  Given(:check_box) { main.find(id: 'checkBox').as :toggle }
  When { check_box.toggle }
  Then { label.name == 'checkBox is on' }
end
