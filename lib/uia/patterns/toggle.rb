module Uia
  module Patterns
    module Toggle
      def toggle_state
        Library.toggle_information(@element).state.to_snake_case_sym
      end

      def toggle_state=(state)
        toggle unless state == toggle_state
      end

      def toggle
        Library.toggle @element
      end
    end
  end
end