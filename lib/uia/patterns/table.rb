module Uia
  module Patterns
    module Table
      module Row
        def items
          find_all(pattern: :table_item).each { |e| e.as :table_item }
        end
      end

      def row_count
        table_info.row_count
      end

      def column_count
        table_info.column_count
      end

      def headers
        Library.table_headers @element
      end

      def rows
        find_all(control_type: :data_item).each { |e| e.extend Row }
      end

      private
      def table_info
        Library.table_info(@element)
      end
    end
  end
end