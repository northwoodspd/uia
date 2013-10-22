require 'spec_helper'

describe Uia::Patterns::Selection do
  let(:main) { find_element id: 'MainFormWindow' }
  Given(:select_list) { main.find(id: 'FruitListBox').as :selection }

  context 'properties' do
    context '#multi_select?' do
      Then { expect(select_list).to_not be_multi_select }
    end

    context '#selection_required?' do
      Then { expect(select_list).to_not be_selection_required }
    end

    context '#selection_items' do
      let(:respond_to_selections) { lambda { |e| e.respond_to? :add_to_selection } }

      Then { select_list.selection_items.map(&:name) == ['Apple', 'Orange', 'Mango'] }
      Then { select_list.selection_items.all?(&respond_to_selections) == true }
    end
  end
end