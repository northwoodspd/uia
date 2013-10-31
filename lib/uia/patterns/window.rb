module Uia
  module Patterns
    module Window
      def visual_state
        Library.window_information(@element).visual_state.downcase.to_sym
      end
    end
  end
end