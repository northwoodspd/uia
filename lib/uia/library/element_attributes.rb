module Uia
  module ElementAttributes
    def element_attr(*attrs)
      attrs.each do |attr|
        define_method(attr) do
          @element.send(attr)
        end
      end
    end
  end
end