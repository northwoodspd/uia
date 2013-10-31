require 'spec_helper'

describe Uia::Patterns::Window do
  Given(:window) { Uia.find_element(id: /MainFormWindow/).as(:window) }

  context 'properties' do
    Then { window.visual_state == :normal }
    Then { window.interaction_state == :ready_for_user_interaction }
  end

  context '#visual_state=' do
    context 'minimized' do
      When { window.visual_state = :minimized }
      Then { window.visual_state == :minimized }
    end

    context 'maximized' do
      When { window.visual_state = :maximized }
      Then { window.visual_state == :maximized }
    end

    context 'normal' do
      When { window.visual_state = :normal }
      Then { window.visual_state == :normal }
    end
  end
end