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
                 :control_type_id, :int,
                 :patterns, :pointer,
                 :patterns_length, :int,
                 :id, :string

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

          def children(type=nil)
            elements = (type && Library.children_of_type(self, type)) || Library.children(self)
            elements.children
          end

          def descendants
            Library.descendants(self).children
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
        @children ||= self[:length].times.collect do |i|
          ElementCast.new(self[:items] + i * ElementCast.size)
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
  end
end
