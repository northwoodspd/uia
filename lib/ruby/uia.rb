require "ruby/uia/version"
require 'ffi'

module Ruby
  module Uia
    extend FFI::Library

    class ElementStruct < FFI::ManagedStruct
      layout :name, :string

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

    def self.find_by_id(id)
      can_throw(:Element_FindById, id)
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
