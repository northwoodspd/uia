require 'uia/library/structs'
require 'ffi'

module Uia
  module Library
    extend FFI::Library

    PropertyId = enum(:is_selection_item, 0)

    def self.uia_directory
      File.dirname(__FILE__) + '/../../ext/UiaDll/Release'
    end

    ffi_lib File.join(uia_directory, 'UiaDll.dll')
    ffi_convention :stdcall

    attach_function :init, :initialize, [:string], :void
    init(uia_directory)

    def self.attach_throwable_function(name_alias, name, arg_types, return_type, &block)
      attach_function name, arg_types + [:pointer, :int], return_type
      define_singleton_method(name_alias) do |*args|
        result = can_throw(name, *args)
        return block.call(result) if block
        result
      end
    end

    # returns nil rather than empty FFI::Struct for Uia::Element
    element_or_nil = lambda { |e| Uia::Element.new(e) unless e.empty? }

    # cleanup
    attach_function :release_element, :Element_Release, [:pointer], :void
    attach_function :release_elements, :Element_ReleaseMany, [:pointer], :void
    attach_function :release_value_info, :Value_Release, [:pointer], :void

    # finding elements
    attach_throwable_function :find_by_id, :Element_FindById, [:string], ElementStruct.by_ref, &element_or_nil
    attach_throwable_function :find_by_name, :Element_FindByName, [:string], ElementStruct.by_ref, &element_or_nil
    attach_throwable_function :find_by_pid, :Element_FindByProcessId, [:int], ElementStruct.by_ref, &element_or_nil
    attach_throwable_function :find_by_handle, :Element_FindByHandle, [:int], ElementStruct.by_ref
    attach_function :Element_FindByRuntimeId, [:pointer, :int, :pointer, :int], ElementStruct.by_ref

    # element methods
    attach_throwable_function :children, :Element_Children, [:pointer], ElementChildrenStruct.by_ref
    attach_throwable_function :children_of_type, :Element_ChildrenOfType, [:pointer, PropertyId], ElementChildrenStruct.by_ref
    attach_throwable_function :descendants, :Element_Descendants, [:pointer], ElementChildrenStruct.by_ref
    attach_throwable_function :click, :Element_Click, [:pointer], :void

    # ValuePattern methods
    attach_throwable_function :set_value, :Value_Set, [:pointer, :string], :void
    attach_throwable_function :value_info, :Value_Information, [:pointer], ValueInformation.by_ref

    def self.find_by_runtime_id(id)
      p = FFI::MemoryPointer.new :int, id.count
      p.write_array_of_int(id)
      result = can_throw(:Element_FindByRuntimeId, p, id.count)
      Uia::Element.new(result) unless result.empty?
    end

    def self.can_throw(method, *args)
      string_buffer = FFI::MemoryPointer.new :char, 1024
      result = send method, *(args << string_buffer << 1024)
      error_info = string_buffer.read_string
      raise error_info unless error_info.empty?
      result
    end

  rescue LoadError => e
    raise LoadError, 'You must install the Visual Studio 2012 C++ Runtime Environment to use the Uia gem (http://www.microsoft.com/en-us/download/details.aspx?id=30679)'
  end
end