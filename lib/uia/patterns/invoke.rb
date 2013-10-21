module Uia
  module Patterns
    module Invoke
      def invoke
        Library.invoke @element
      end
    end
  end
end
