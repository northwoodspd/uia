require 'spec_helper'

describe Element do
  context 'properties' do
    Given(:element) { find_element(id: 'MainFormWindow') }

    Then { element.handle != 0 }
    Then { element.name == 'MainFormWindow' }
    Then { element.children.count == 27 }
  end
end