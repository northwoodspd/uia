module Uia
  module Patterns
    module Toggle
      def toggle_state
        Library.toggle_information(@element).state.downcase.to_sym
      end

      def toggle
        Library.toggle @element
      end
    end
  end
end