module Uia
  module ControlTypes
    module MenuItems
      def select_menu_path(*path)
        Library.select_menu_path @element, *path
      end
      alias_method :select_menu_item, :select_menu_path

      def has_menu_item?(*path)
        Library.has_menu_item @element, *path
      end
    end
  end
end