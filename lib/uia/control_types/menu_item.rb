module Uia
  module ControlTypes
    module MenuItems
      def select_menu_item(*path)
        Library.select_menu_path @element, *path
      end

      def menu_item(*path)
        Library.menu_item @element, *path
      end
    end
  end
end