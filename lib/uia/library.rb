require 'ffi'
require 'uia/library/element_structs'
require 'uia/library/pattern_structs'

module Uia
  module Library
    extend FFI::Library

    def self.uia_directory
      File.dirname(__FILE__) + '/../../ext/UiaDll/Release'
    end

    ffi_lib File.join(uia_directory, 'UiaDll.dll')
    ffi_convention :stdcall

    attach_function :init, :initialize, [:string], :void
    init(uia_directory)

    attach_function :warm_up_automation, :Automation_WarmUp, [], :void
    warm_up_automation

    def self.attach_throwable_function(name_alias, name, arg_types, return_type, &block)
      attach_function name, arg_types + [:pointer, :int], return_type
      define_singleton_method(name_alias) do |*args|
        result = can_throw(name, *args)
        return block.call(result) if block
        result
      end
    end

    def self.elements_from(name_alias, name, arg_types, &block)
      attach_function name, arg_types + [:pointer, :pointer, :int], :int
      define_singleton_method(name_alias) do |*args|
        elements_pointer = FFI::MemoryPointer.new :pointer
        can_throw(name, *(args << elements_pointer)).times.collect do |which_element|
          pointer = elements_pointer.read_pointer + which_element * ManagedElementStruct.size
          Uia::Element.new(ManagedElementStruct.new(pointer))
        end
      end
    end

    # returns nil rather than empty FFI::Struct for Uia::Element
    element_or_nil = lambda { |e| Uia::Element.new(e) unless e.empty? }

    # cleanup
    attach_function :release_element, :Element_Release, [:pointer], :void
    attach_function :release_window_info, :Window_Release, [:pointer], :void
    attach_function :release_value_info, :Value_Release, [:pointer], :void
    attach_function :release_toggle_info, :Toggle_Release, [:pointer], :void
    attach_function :release_selection_info, :Selection_Release, [:pointer], :void
    attach_function :release_selection_item_info, :SelectionItem_Release, [:pointer], :void
    attach_function :release_table_info, :Table_Release, [:pointer], :void
    attach_function :release_table_item_info, :TableItem_Release, [:pointer], :void
    attach_function :release_expand_collapse_info, :ExpandCollapse_Release, [:pointer], :void
    attach_function :release_range_value_info, :RangeValue_Release, [:pointer], :void

    # root methods
    elements_from :root_children, :Root_Children, []

    # finding elements
    attach_throwable_function :find_by_id, :Element_FindById, [:string], ManagedElementStruct.by_ref, &element_or_nil
    attach_throwable_function :find_by_name, :Element_FindByName, [:string], ManagedElementStruct.by_ref, &element_or_nil
    attach_throwable_function :find_by_pid, :Element_FindByProcessId, [:int], ManagedElementStruct.by_ref, &element_or_nil
    attach_throwable_function :find_by_handle, :Element_FindByHandle, [:int], ManagedElementStruct.by_ref, &element_or_nil
    attach_function :Element_FindByRuntimeId, [:pointer, :int, :pointer, :int], ManagedElementStruct.by_ref
    attach_function :FindFirst, [:pointer, :string, :pointer, :int, :int, :varargs], ManagedElementStruct.by_ref
    attach_function :FindAll, [:pointer, :pointer, :string, :pointer, :int, :int, :varargs], :int

    ## conditions
    attach_function :release_condition, :Condition_Release, [:pointer], :void
    attach_function :id_condition, :Condition_Id, [:string], SearchCondition.by_ref
    attach_function :Condition_Pattern, [:pointer, :int, :int, :varargs], SearchCondition.by_ref
    attach_function :name_condition, :Condition_Name, [:string], SearchCondition.by_ref
    self.singleton_class.send(:alias_method, :value_condition, :name_condition)
    attach_function :Condition_ControlType, [:int, :varargs], SearchCondition.by_ref

    def self.pattern_condition(*patterns)
      try_catch do |s, n|
        pattern_strings = patterns.flatten.map(&:to_pattern_available_property)
        Condition_Pattern s, n, pattern_strings.count, *pattern_strings.to_var_args(:string)
      end
    end

    def self.control_type_condition(*control_types)
      control_type_ids = control_types.flatten.map(&:to_control_type_const)
      Condition_ControlType control_type_ids.count, *control_type_ids.to_var_args(:int)
    end

    # element methods
    attach_throwable_function :send_keys, :Element_SendKeys, [:pointer, :string], :void
    elements_from :children, :Element_Children, [:pointer]
    elements_from :descendants, :Element_Descendants, [:pointer]
    attach_throwable_function :click, :Element_ClickClickablePoint, [:pointer], :void
    attach_throwable_function :click_center, :Element_ClickCenter, [:pointer], :void
    attach_throwable_function :focus, :Element_Focus, [:pointer], :void
    attach_throwable_function :refresh, :Element_Refresh, [:pointer], :void

    # mouse methods
    attach_throwable_function :drag, :Mouse_Drag, [:int, :int, :int, :int], :void

    # WindowPattern methods
    attach_throwable_function :window_information, :Window_Information, [:pointer], WindowInformation.by_ref
    attach_throwable_function :set_visual_state, :Window_SetVisualState, [:pointer, :string], :void
    attach_throwable_function :close_window, :Window_Close, [:pointer], :void

    # ValuePattern methods
    attach_throwable_function :set_value, :Value_Set, [:pointer, :string], :void
    attach_throwable_function :value_info, :Value_Information, [:pointer], ValueInformation.by_ref

    # ExpandCollapsePattern methods
    attach_throwable_function :expand_collapse_info, :ExpandCollapse_Information, [:pointer], ExpandCollapseInformation.by_ref
    attach_throwable_function :expand, :ExpandCollapse_Expand, [:pointer], :void
    attach_throwable_function :collapse, :ExpandCollapse_Collapse, [:pointer], :void

    # InvokePattern methods
    attach_throwable_function :invoke, :Invoke, [:pointer], :void

    # TogglePattern methods
    attach_throwable_function :toggle_information, :Toggle_Information, [:pointer], ToggleInformation.by_ref
    attach_throwable_function :toggle, :Toggle, [:pointer], :void

    # SelectionPattern methods
    attach_throwable_function :selection_info, :Selection_Information, [:pointer], SelectionInformation.by_ref
    elements_from :selected_items, :Selection_Selections, [:pointer]

    # SelectionItemPattern methods
    attach_throwable_function :selection_item_info, :SelectionItem_Information, [:pointer], SelectionItemInformation.by_ref
    attach_throwable_function :select, :SelectionItem_Select, [:pointer], :void
    attach_throwable_function :add_to_selection, :SelectionItem_AddToSelection, [:pointer], :void
    attach_throwable_function :remove_from_selection, :SelectionItem_RemoveFromSelection, [:pointer], :void

    # TablePattern methods
    attach_throwable_function :table_info, :Table_Information, [:pointer], TableInformation.by_ref
    attach_throwable_function :table_row, :Table_Row, [:pointer, :int], ManagedElementStruct.by_ref, &element_or_nil
    elements_from :table_headers, :Table_Headers, [:pointer]

    # TableItemPattern methods
    attach_throwable_function :table_item_info, :TableItem_Information, [:pointer], TableItemInformation.by_ref

    # RangeValuePattern methods
    attach_throwable_function :range_value_info, :RangeValue_Information, [:pointer], RangeValueInformation.by_ref
    attach_throwable_function :set_range_value, :RangeValue_SetValue, [:pointer, :double], :void

    # TextPattern methods
    attach_function :Text_GetText, [:pointer, :pointer, :int, :pointer, :int], :int

    def self.get_text(element)
      length = can_throw(:Text_GetText, element, nil, 0) + 1
      p = FFI::MemoryPointer.new :pointer, length
      can_throw(:Text_GetText, element, p, length)
      p.read_string
    end

    # MenuItem methods
    attach_function :MenuItem_SelectPath, [:pointer, :pointer, :int, :int, :varargs], :void
    attach_function :MenuItem_ByPath, [:pointer, :pointer, :int, :int, :varargs], ManagedElementStruct.by_ref

    def self.select_menu_path(element, *path)
      try_catch {|s, n| MenuItem_SelectPath element, s, n, path.count, *path.to_var_args(:string) }
    end

    def self.menu_item(element, *path)
      e = try_catch {|s, n| MenuItem_ByPath element, s, n, path.count, *path.to_var_args(:string) }
      Uia::Element.new(e) unless e.empty?
    end

    def self.find_by_runtime_id(id)
      p = FFI::MemoryPointer.new :int, id.count
      p.write_array_of_int(id)
      result = can_throw(:Element_FindByRuntimeId, p, id.count)
      Uia::Element.new(result) unless result.empty?
    end

    def self.try_catch(&block)
      buffer_size = 4096
      string_buffer = FFI::MemoryPointer.new :char, buffer_size
      result = block.call(string_buffer, buffer_size)
      error_info = string_buffer.read_string
      raise error_info unless error_info.empty?
      result
    end

    def self.can_throw(method, *args)
      try_catch {|s, n| send method, *(args << s << n) }
    end

    def self.find_first(element, scope, *conditions)
      result = try_catch {|s, n| FindFirst element, scope, s, n, conditions.count, *conditions.to_var_args(:pointer) }
      Uia::Element.new(result) unless result.empty?
    end

    def self.find_all(element, scope, *conditions)
      elements_pointer = FFI::MemoryPointer.new :pointer
      result = try_catch {|s, n| FindAll element, elements_pointer, scope, s, n, conditions.count, *conditions.to_var_args(:pointer) }
      result.times.collect do |which_element|
        pointer = elements_pointer.read_pointer + which_element * ManagedElementStruct.size
        Uia::Element.new(ManagedElementStruct.new(pointer))
      end
    end

  rescue LoadError
    raise LoadError, 'You must install the Visual Studio 2012 C++ Runtime Environment to use the Uia gem (http://www.microsoft.com/en-us/download/details.aspx?id=30679)'
  end
end