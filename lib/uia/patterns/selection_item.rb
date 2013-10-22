module Uia
  module Patterns
    module SelectionItem
      def select
        Library.select @element
      end

      def selected?
        Library.selection_item_info(@element).selected?
      end
    end
  end
end