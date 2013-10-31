require 'spec_helper'

describe Uia::Patterns::Table do
  Given(:data_grid) do
    until (form = Uia.find_element(name: 'DataEntryForm'))
      Uia.find_element(id: /MainForm/).find(name: 'Data Entry Form').as(:invoke).invoke
    end

    form.find(name: 'Add Many').as(:invoke).invoke
    form.find(id: 'personListView').as(:table)
  end

  context 'properties' do
    Then { data_grid.row_count == 52 }
    Then { data_grid.column_count == 3 }
  end

  context '#headers' do
    Then { data_grid.headers.map(&:control_type) == [:header_item] * 3 }
    Then { data_grid.headers.map(&:name) == ['Name', 'Date of birth', 'State'] }
  end
end