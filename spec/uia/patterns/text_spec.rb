require 'spec_helper'

describe Uia::Patterns::Text do
  Given(:text_field) do
    Uia.find_element(id: 'MainFormWindow').children.find { |e| e.id == 'multiLineTextField' }.as :text
  end

  context '#text' do
    context 'getting / setting' do
      When { text_field.text = '{text} to be expected!' }
      Then { text_field.text == '{text} to be expected!' }
    end

    context 'updating' do
      Given { text_field.text = 'about to be overwritten' }
      When { text_field.text = 'expected update' }
      Then { text_field.text == 'expected update' }
    end
  end
end