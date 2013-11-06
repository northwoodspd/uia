require 'uia/library/win32'

module Uia
  class BadLocator < StandardError
    def initialize(locator)
      super "#{locator} is not a valid locator"
    end
  end
  class BadChildLocator < BadLocator; end

  module Finder
    def find_from_root(locator)
      case
        when locator[:id]
          find_by_id locator[:id]
        when locator[:name]
          find_by_name locator[:name]
        when locator[:pid]
          find_by_pid locator[:pid]
        when locator[:runtime_id]
          find_by_runtime_id locator[:runtime_id]
        when locator[:handle]
          find_by_handle locator[:handle]
        when locator[:title]
          find_by_title locator[:title]
        else
          raise BadLocator, locator
      end
    end

    def find_child(parent, locator)
      scope = (locator[:scope] || :descendants).to_s.capitalize

      case
        when locator[:id]
          find_child_by_id parent, locator[:id], scope
        when locator[:name]
          find_child_by_name parent, locator[:name], scope
        when locator[:title]
          find_by_title locator[:title], parent.handle
        else
          raise BadChildLocator, locator
      end
    end

    private
    def find_by_id(id)
      find_by_property(:id, id)
    end

    def find_child_by_id(parent, id, scope)
      Library.find_child_by_id(parent, id, (scope || :descendants).to_s.capitalize)
    end

    def find_by_name(name)
      find_by_property(:name, name)
    end

    def find_child_by_name(parent, name, scope)
      Library.find_child_by_name(parent, name, (scope || :descendants).to_s.capitalize)
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
