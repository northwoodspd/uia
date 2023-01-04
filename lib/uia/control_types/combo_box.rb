module Uia
  module ControlTypes
    module ComboBox

      def items
        Library.combo_box_items @element
      end

    end
  end
end