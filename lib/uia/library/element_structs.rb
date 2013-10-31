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

    module ElementChildrenLayout
      def self.included(base)
        base.class_eval do
          layout :length, :int,
                 :items, :pointer

          def children
            self[:length].times.collect do |i|
              pointer = self[:items] + i * ElementCast.size
              Uia::Element.new(ElementCast.new(pointer))
            end
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
      include ElementChildrenLayout

      def self.release(pointer)
        Library.release_elements(pointer)
      end
    end

    class ElementChildrenCast < FFI::Struct
      include ElementChildrenLayout
    end
  end
end
