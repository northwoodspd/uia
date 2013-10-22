module Uia
  module Patterns
    module SelectionItem
      def select
        Library.select @element
      end

      def selected?
        Library.selection_item_info(@element).selected?
      end

      def container
        Uia::Element.new Library.selection_item_info(@element).container
      end
    end
  end
end