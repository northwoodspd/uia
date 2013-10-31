require 'spec_helper'

describe Uia::Patterns::Window do
  Given(:window) { Uia.find_element(id: /MainFormWindow/).as(:window) }

  context 'properties' do
    Then { window.visual_state == :normal }
    Then { window.interaction_state == :ready_for_user_interaction }
  end
end