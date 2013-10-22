module Uia
  module Patterns
    module SelectionItem
      def select
        Library.select @element
      end

      def add_to_selection
        Library.add_to_selection @element
      end

      def remove_from_selection
        Library.remove_from_selection @element
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