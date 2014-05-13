module Uia
  module ControlTypes
    module MenuItems
      def select_menu_path(*path)
        Library.select_menu_path @element, *path
      end
      alias_method :select_menu_item, :select_menu_path
    end
  end
end