module Uia
  module Patterns
    module Selection
      def selection_items
        descendants.map {|e| e.as :selection_item }
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