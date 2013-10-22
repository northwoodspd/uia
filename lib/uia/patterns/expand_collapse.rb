module Uia
  module Patterns
    module ExpandCollapse
      def expand_collapse_state
        Library.expand_collapse_info(@element).expand_collapse_state.downcase.to_sym
      end
    end
  end
end