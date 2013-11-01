module Uia
  module Patterns
    module TableItem
      def column
        table_item_info.column
      end

      def row
        table_item_info.row
      end

      private
      def table_item_info
        Library.table_item_info(@element)
      end
    end
  end
end