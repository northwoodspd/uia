require 'spec_helper'

describe Uia::Patterns::TableItem do
  Given(:data_grid) do
    until (form = Uia.find_element(name: 'DataEntryForm'))
      Uia.find_element(id: /MainForm/).find(name: 'Data Entry Form').as(:invoke).invoke
    end

    form.find(name: 'Add Many').as(:invoke).invoke
    form.find(id: 'personListView').as(:table)
  end
  Given(:first_row) { data_grid.rows.first }

  context 'properties' do
    Given(:first_item) { first_row.items.first }
    Given(:last_item) { first_row.items.last }

    Then { last_item.column == 2 }
    Then { first_item.row == 0 }
  end
end
