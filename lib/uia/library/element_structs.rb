require 'ffi'

require 'uia/library/struct_attributes'

module Uia
  module Library
    module ElementLayout
      def self.included(base)
        base.class_eval do
          extend StructAttributes

          layout :handle, :int,
                 :runtime_id, :pointer,
                 :number_of_ids, :int,
                 :name, :string,
                 :help_text, :string,
                 :class_name, :string,
                 :control_type_id, :int,
                 :patterns, :pointer,
                 :patterns_length, :int,
                 :id, :string,
                 :is_enabled, :bool,
                 :is_visible, :bool,
                 :has_focus, :bool,
                 :bounding_rectangle, [:long, 4]

          struct_attr :id, :name, :handle, :control_type_id, :class_name, :help_text,
                      [:enabled?, :is_enabled], [:visible?, :is_visible], [:focused?, :has_focus]

          def runtime_id
            self[:runtime_id].read_array_of_int(number_of_ids)
          end

          def bounding_rectangle
            self[:bounding_rectangle].to_a
          end

          def pattern_ids
            self[:patterns].read_array_of_int(self[:patterns_length])
          end

          def children
            Library.children(self)
          end

          def descendants
            Library.descendants(self)
          end

          def empty?
            to_ptr.address == 0
          end

          private
          def number_of_ids
            self[:number_of_ids]
          end
        end
      end
    end

    class ManagedElementStruct < FFI::ManagedStruct
      include ElementLayout

      def self.release(pointer)
        Library.release_element(pointer)
      end
    end

    class ElementStruct < FFI::Struct
      include ElementLayout
    end

    class SearchCondition < FFI::ManagedStruct
      extend StructAttributes

      layout :property_id, :int,
             :int_value, :int,
             :string_value, :string,
             :numbers, :pointer,
             :numbers_count, :int

      struct_attr :property_id, :int_value, :string_value

      def numbers
        self[:numbers].read_array_of_int self[:numbers_count]
      end

      def self.release(pointer)
        Library.release_condition(pointer)
      end
    end
  end
end
