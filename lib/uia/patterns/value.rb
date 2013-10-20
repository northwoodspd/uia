module Uia
  module Patterns
    module Value
      def value=(value)
        Library.set_value(@element, value)
      end

      def value
        value_information.value
      end

      def read_only?
        value_information.read_only?
      end

      private
      def value_information
        Library.value_info(@element)
      end
    end
  end
end
