require 'spec_helper'

describe Element do
  Given(:element) { find_element(id: 'MainFormWindow') }
  Given(:about_box) { find_element(id: 'AboutBox') }

  context 'properties' do
    Then { element.handle != 0 }
    Then { element.name == 'MainFormWindow' }
  end

  context '#click' do
    Given(:about) { element.children.find {|c| c.name == 'About'} }
    When { about.click }
    Then { about_box != nil }
    And { about_box.children.find {|c| c.name == 'OK'}.click }
  end

  context '#children' do
    Then { element.children.count == 27 }
    Then { element.children.all? { |c| c.instance_of? Element } }
  end
end
