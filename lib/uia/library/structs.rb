require 'ffi'

module Uia
  module Library
    module ElementLayout
      def self.included(base)
        base.class_eval do
          layout :handle, :int,
                 :runtime_id, :pointer,
                 :number_of_ids, :int,
                 :name, :string,
                 :class_name, :string,
                 :control_type_id, :int,
                 :patterns, :pointer,
                 :patterns_length, :int,
                 :id, :string,
                 :is_enabled, :bool

          def id
            self[:id]
          end

          def name
            self[:name]
          end

          def handle
            self[:handle]
          end

          def runtime_id
            self[:runtime_id].read_array_of_int(number_of_ids)
          end

          def control_type_id
            self[:control_type_id]
          end

          def pattern_ids
            self[:patterns].read_array_of_int(self[:patterns_length])
          end

          def children
            Library.children(self).children
          end

          def descendants
            Library.descendants(self).children
          end

          def empty?
            to_ptr.address == 0
          end

          def enabled?
            self[:is_enabled]
          end

          def class_name
            self[:class_name]
          end

          private
          def number_of_ids
            self[:number_of_ids]
          end
        end
      end
    end

    class ElementStruct < FFI::ManagedStruct
      include ElementLayout

      def self.release(pointer)
        Library.release_element(pointer)
      end
    end

    class ElementCast < FFI::Struct
      include ElementLayout
    end

    class ElementChildrenStruct < FFI::ManagedStruct
      layout :length, :int,
             :items, :pointer

      def children
        self[:length].times.collect do |i|
          pointer = self[:items] + i * ElementCast.size
          Uia::Element.new(ElementCast.new(pointer))
        end
      end

      def self.release(pointer)
        Library.release_elements(pointer)
      end
    end

    class ValueInformation < FFI::ManagedStruct
      layout :is_read_only, :bool,
             :value, :string

      def read_only?
        self[:is_read_only]
      end

      def value
        self[:value]
      end

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
             :container, ElementCast.ptr

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
      layout :visual_state, :string,
             :interaction_state, :string,
             :can_minimize, :bool,
             :can_maximize, :bool,
             :is_modal, :bool,
             :is_topmost, :bool

      def visual_state
        self[:visual_state]
      end

      def can_minimize?
        self[:can_minimize]
      end

      def can_maximize?
        self[:can_maximize]
      end

      def modal?
        self[:is_modal]
      end

      def topmost?
        self[:is_topmost]
      end

      def interaction_state
        self[:interaction_state]
      end

      def self.release(pointer)
        Library.release_window_info(pointer)
      end
    end

    class TableInformation < FFI::ManagedStruct
      layout :row_count, :int,
             :column_count, :int

      def row_count
        self[:row_count]
      end

      def column_count
        self[:column_count]
      end

      def self.release(pointer)
        Library.release_table_info(pointer)
      end
    end
  end
end
