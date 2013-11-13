module Uia
  module Patterns
    module Text
      def text=(value)
        send_keys [:control, :home], [:control, :shift, :end], value
      end

      def text
        Library.get_text @element
      end
    end
  end
end