require 'spec_helper'

describe Uia::Patterns::ExpandCollapse do
  let(:main) { find_element id: 'MainFormWindow' }

  Given(:parent_one) { main.find(name: 'Parent One').as :expand_collapse }

  context 'properties' do
    context '#expand_collapse_state' do
      Then { parent_one.expand_collapse_state == :collapsed }
    end
  end
end