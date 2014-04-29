require 'spec_helper'

describe Symbol do

  context '#to_control_type_const' do
    Then { expect(:list_item.to_control_type_const).to eq(50007) }
    Then { expect { :not_a_control_type.to_control_type_const }.to raise_error InvalidControlType }
  end
end