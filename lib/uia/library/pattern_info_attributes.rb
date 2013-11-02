module Uia
  module PatternInfoAttributes
    def pattern_attr(*attrs)
      attrs.each do |attr|
        define_method(attr) do
          pattern_info.send(attr)
        end
      end
    end
  end
end