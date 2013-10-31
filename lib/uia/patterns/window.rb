module Uia
  module Patterns
    module Window
      def visual_state
        window_information.visual_state.to_snake_case_sym
      end

      def can_minimize?
        window_information.can_minimize?
      end

      def can_maximize?
        window_information.can_maximize?
      end

      def modal?
        window_information.modal?
      end

      def topmost?
        window_information.topmost?
      end

      def visual_state=(state)
        Library.set_visual_state(@element, state.to_camelized_s)
      end

      def interaction_state
        window_information.interaction_state.to_snake_case_sym
      end

      private
      def window_information
        Library.window_information(@element)
      end
    end
  end
end