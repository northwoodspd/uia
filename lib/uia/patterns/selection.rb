module Uia
  module Patterns
    module Selection
      def selection_items
        find_all(pattern: :selection_item).map {|e| e.as :selection_item }
      end

      def selected_items
        Library.selected_items(@element).map {|e| e.as :selection_item }
      end

      def multi_select?
        Library.selection_info(@element).multi_select?
      end

      def selection_required?
        Library.selection_info(@element).selection_required?
      end
    end
  end
end