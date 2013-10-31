require 'spec_helper'

describe Uia::Patterns::Window do
  Given(:window) { Uia.find_element(id: /MainFormWindow/).as(:window) }

  context '#visual_state' do
    Then { window.visual_state == :normal }
  end
end