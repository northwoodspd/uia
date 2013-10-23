require 'spec_helper'

describe Uia::Patterns::Toggle do
  let(:main) { Uia.find_element id: 'MainFormWindow' }
  let(:label) { main.find id: 'checkBoxLabel' }

  Given(:check_box) { main.find(id: 'checkBox').as :toggle }

  context 'properties' do
    When { check_box.toggle }

    Then { check_box.toggle_state == :on }
    Then { check_box.toggle_state == :off }
  end

  context '#toggle' do
    When { check_box.toggle }
    Then { label.name == 'checkBox is on' }
  end

  context '#toggle=' do
    Given { check_box.toggle unless check_box.toggle_state == :off }

    context ':off to :on' do
      When { check_box.toggle_state = :on }
      Then { check_box.toggle_state == :on }
    end

    context ':on to :off' do
      Given { check_box.toggle_state = :on }
      When { check_box.toggle_state = :off }
      Then { check_box.toggle_state == :off }
    end

    context '<state> to <same state>' do
      Given!(:original_state) { check_box.toggle_state }
      When { check_box.toggle_state = original_state }
      Then { check_box.toggle_state == original_state }
    end
  end
end
