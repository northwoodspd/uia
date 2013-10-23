require 'spec_helper'

describe Uia::Patterns::Invoke do
  let(:main) { Uia.find_element id: 'MainFormWindow' }
  let(:radio_label) { main.find(id: 'radioButtonLabel') }

  Given(:reset) { main.find(name: 'Reset').as :invoke }

  context '#invoke' do
    Given { main.find(name: 'Option 2').click }

    When { reset.invoke }
    Then { radio_label.name == 'No option selected' }
  end
end