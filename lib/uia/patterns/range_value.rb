module Uia
  module Patterns
    module RangeValue
      extend PatternInfoAttributes

      pattern_attr :value, :minimum, :maximum,
                   :small_change, :large_change, :read_only?

      def value=(num)
        Library.set_range_value @element, num
      end

      private
      def pattern_info
        Library.range_value_info @element
      end
    end
  end
end