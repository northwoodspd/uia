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
    Then { data_grid.headers.map(&:name) == ['Full Name', 'Date of birth', 'State'] }
  end

  context '#rows' do
    Then { data_grid.rows.count == data_grid.row_count }

    context 'row' do
      Given(:row) { data_grid.rows[0] }

      context '#items' do
        Then { row.items.map(&:name) == ['John Doe', '12/15/1967', 'FL'] }
      end
    end
  end

  context '#row_at' do
    Then { data_grid.row_at(1).items[1].name == '3/4/1975'}
  end
end