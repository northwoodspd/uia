require 'ffi'

module Win32
  extend FFI::Library

  ffi_lib 'user32'

  callback :enum_callback, [:long, :long], :bool

  attach_function :enum_windows, :EnumWindows,
                  [:enum_callback, :long], :long
  attach_function :_window_title, :GetWindowTextA,
                  [:long, :pointer, :int], :int
  attach_function :window_title_length, :GetWindowTextLengthA,
                  [:long], :int

  class << self
    def window_title(handle)
      length = window_title_length(handle) + 1
      title = FFI::MemoryPointer.new :char, length
      _window_title handle, title, length
      title.read_string
    end

    def find_window(&block)
      found_window = nil
      window_callback = FFI::Function.new(:bool, [:long, :pointer], {convention: :stdcall}) do |handle, _|
        found_window = handle if block.call handle
        !found_window
      end
      Win32.enum_windows window_callback, 0
      found_window
    end
  end
end
