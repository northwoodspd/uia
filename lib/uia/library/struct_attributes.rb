module Uia
  module StructAttributes
    def struct_attr(*attrs)
      attrs.each do |attr|
        meth, aka = attr
        define_method(meth) do
          self[aka || meth]
        end
      end
    end
  end
end