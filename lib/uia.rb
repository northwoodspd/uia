require 'uia/version'
require 'ffi'

module Uia
  extend FFI::Library

  module ElementLayout
    def self.included(base)
      base.class_eval do
        layout :handle, :int,
               :runtime_id, :pointer,
               :number_of_ids, :int,
               :name, :string

        def handle
          self[:handle]
        end

        def runtime_id
          self[:runtime_id].read_array_of_int(number_of_ids)
        end

        def number_of_ids
          self[:number_of_ids]
        end

        def children
          Uia.children(self).children
        end

        def name
          self[:name]
        end

        def click
          Uia.click(self)
        end
      end
    end
  end

  class ElementStruct < FFI::ManagedStruct
    include ElementLayout

    def self.release(pointer)
      Uia.release_element(pointer)
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
      Uia.release_elements(pointer)
    end
  end

  def self.uia_directory
    File.dirname(__FILE__) + '/../ext/UiaDll/Release'
  end

  ffi_lib File.join(uia_directory, 'UiaDll.dll')
  ffi_convention :stdcall

  attach_function :init, :initialize, [:string], :void
  init(uia_directory)

  def self.attach_throwable_function(name_alias, name, arg_types, return_type)
    attach_function name, arg_types + [:pointer, :int], return_type
    define_singleton_method(name_alias) do |*args|
      can_throw(name, *args)
    end
  end

  # cleanup
  attach_function :release_element, :Element_Release, [:pointer], :void
  attach_function :release_elements, :Element_ReleaseMany, [:pointer], :void

  # finding elements
  attach_throwable_function :find_by_id, :Element_FindById, [:string], ElementStruct.by_ref
  attach_throwable_function :find_by_handle, :Element_FindByHandle, [:int], ElementStruct.by_ref
  attach_function :Element_FindByRuntimeId, [:pointer, :int, :pointer, :int], ElementStruct.by_ref

  # element methods
  attach_throwable_function :children, :Element_Children, [:pointer], ElementChildrenStruct.by_ref
  attach_throwable_function :click, :Element_Click, [:pointer], :void

  def self.find_by_runtime_id(id)
    p = FFI::MemoryPointer.new :int, id.count
    p.write_array_of_int(id)
    can_throw(:Element_FindByRuntimeId, p, id.count)
  end

  def self.can_throw(method, *args)
    string_buffer = FFI::MemoryPointer.new :char, 1024
    result = send method, *(args << string_buffer << 1024)
    error_info = string_buffer.read_string
    raise error_info unless error_info.empty?
    result
  end
end
