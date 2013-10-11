require "ruby/uia/version"
require 'ffi'

module Ruby
  module Uia
    extend FFI::Library

    class ElementStruct < FFI::ManagedStruct
      layout  :runtime_id, :pointer,
              :number_of_ids, :int,
              :name, :string

      def runtime_id
        self[:runtime_id].read_array_of_int(number_of_ids)
      end

      def method_missing(meth, *args, &block)
        self[meth.to_sym] || super(meth, *args, &block)
      end

      def self.release(pointer)
        Uia.release_element(pointer)
      end
    end

    def self.uia_directory
      File.dirname(__FILE__) + '/../../ext/UiaDll/Release'
    end

    ffi_lib File.join(uia_directory, 'UiaDll.dll')
    ffi_convention :stdcall

    attach_function :init, :initialize, [:string], :void
    init(uia_directory)

    attach_function :release_element, :Element_Release, [:pointer], :void
    attach_function :Element_FindById, [:string, :pointer, :int], ElementStruct.by_ref
    attach_function :Element_FindByRuntimeId, [:pointer, :int, :pointer, :int], ElementStruct.by_ref

    def self.find_by_id(id)
      can_throw(:Element_FindById, id)
    end

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
end
