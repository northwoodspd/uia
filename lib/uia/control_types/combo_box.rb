module Uia
  module ControlTypes
    module ComboBox

      def items
        Library.combo_box_items @element
      end

      def set(value)
        case value
        when String
          Library.combo_box_set_item_by_value @element, value
        when Regexp
          found_item = items.find { |e| e.name =~ value }
          if found_item
            Library.combo_box_set_item_by_value @element, found_item.name
          end
        when Fixnum
          Library.combo_box_set_item_by_index @element, value
        end
      end

    end
  end
end