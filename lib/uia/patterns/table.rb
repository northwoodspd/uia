module Uia
  module Patterns
    module Table
      def row_count
        table_info.row_count
      end

      def column_count
        table_info.column_count
      end

      private
      def table_info
        Library.table_info(@element)
      end
    end
  end
end