require 'uia/library/win32'

module Uia
  module Finder
    def find_by_id(id)
      find_by_property(:id, id)
    end

    def find_by_name(name)
      find_by_property(:name, name)
    end

    def find_by_pid(pid)
      Library.find_by_pid(pid)
    end

    def find_by_runtime_id(runtime_id)
      Library.find_by_runtime_id(runtime_id)
    end

    def find_by_handle(handle)
      Library.find_by_handle handle
    end

    def find_by_title(title, parent=0)
      found_window = Win32.find_window(parent) do |handle|
        case title
          when Regexp
            Win32.window_title(handle) =~ title
          else
            Win32.window_title(handle) == title
        end
      end
      find_by_handle found_window if found_window
    rescue
      nil
    end

    private
    def find_by_property(property, what)
      case what
        when String
          Library.send("find_by_#{property}", what)
        when Regexp
          children.find { |e| e.send(property) =~ what }
      end
    end
  end
end
