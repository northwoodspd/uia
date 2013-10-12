require 'spec_helper'

describe Element do
  Given(:element) { find_element(id: 'MainFormWindow') }

  context 'properties' do
    Then { element.handle != 0 }
    Then { element.name == 'MainFormWindow' }
  end

  context '#children' do
    Then { element.children.count == 27 }
    Then { element.children.all? { |c| c.instance_of? Element } }
  end
end
