module Uia
  module Patterns
    module Table
      module Row
        def items
          select(pattern: :table_item).each { |e| e.as :table_item }
        end
      end

      def row_count
        table_info.row_count
      end

      def column_count
        table_info.column_count
      end

      def headers
        table_info.headers
      end

      def rows
        select(control_type: :data_item).each { |e| e.extend Row }
      end

      private
      def table_info
        Library.table_info(@element)
      end
    end
  end
end