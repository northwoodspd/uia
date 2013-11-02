require 'uia/library/struct_attributes'

module Uia
  module Library
    class ValueInformation < FFI::ManagedStruct
      extend StructAttributes

      layout :is_read_only, :bool,
             :value, :string

      struct_attr [:read_only?, :is_read_only], :value

      def self.release(pointer)
        Library.release_value_info(pointer)
      end
    end

    class ToggleInformation < FFI::ManagedStruct
      layout :state, :string

      def state
        self[:state]
      end

      def self.release(pointer)
        Library.release_toggle_info(pointer)
      end
    end

    class SelectionInformation < FFI::ManagedStruct
      layout :can_multi_select, :bool,
             :is_selection_required, :bool

      def multi_select?
        self[:can_multi_select]
      end

      def selection_required?
        self[:is_selection_required]
      end

      def self.release(pointer)
        Library.release_selection_info(pointer)
      end
    end

    class SelectionItemInformation < FFI::ManagedStruct
      layout :is_selected, :bool,
             :container, ElementStruct.ptr

      def selected?
        self[:is_selected]
      end

      def container
        self[:container] unless self[:container].empty?
      end

      def self.release(pointer)
        Library.release_selection_item_info(pointer)
      end
    end

    class ExpandCollapseInformation < FFI::ManagedStruct
      layout :expand_collapse_state, :string

      def expand_collapse_state
        self[:expand_collapse_state]
      end

      def self.release(pointer)
        Library.release_expand_collapse_info(pointer)
      end
    end

    class WindowInformation < FFI::ManagedStruct
      extend StructAttributes

      layout :visual_state, :string,
             :interaction_state, :string,
             :can_minimize, :bool,
             :can_maximize, :bool,
             :is_modal, :bool,
             :is_topmost, :bool

      struct_attr :visual_state, [:can_minimize?, :can_minimize], [:can_maximize?, :can_maximize],
                  [:modal?, :is_modal], [:topmost?, :is_topmost], :interaction_state

      def self.release(pointer)
        Library.release_window_info(pointer)
      end
    end

    class TableInformation < FFI::ManagedStruct
      extend StructAttributes

      layout :row_count, :int,
             :column_count, :int,
             :headers, Elements.ptr

      struct_attr :row_count, :column_count

      def headers
        self[:headers].children
      end

      def self.release(pointer)
        Library.release_table_info(pointer)
      end
    end

    class TableItemInformation < FFI::ManagedStruct
      extend StructAttributes

      layout :column, :int,
             :row, :int

      struct_attr :column, :row

      def self.release(pointer)
        Library.release_table_item_info(pointer)
      end
    end

    class RangeValueInformation < FFI::ManagedStruct
      extend StructAttributes

      layout :value, :double,
             :minimum, :double,
             :maximum, :double,
             :small_change, :double,
             :large_change, :double,
             :is_read_only, :bool

      struct_attr :value, :minimum, :maximum, :small_change, :large_change, [:read_only?, :is_read_only]

      def self.release(pointer)
        Library.release_range_value_info(pointer)
      end
    end
  end
end