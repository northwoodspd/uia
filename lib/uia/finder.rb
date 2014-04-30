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
        when locator[:name], locator[:value]
          find_by_name locator[:name] || locator[:value]
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
      scope = (locator.delete(:scope) || :descendants).to_s.capitalize

      valid_locators = [:title, :handle, :id, :name, :value, :control_type, :pattern, :scope]
      raise BadChildLocator, locator unless (locator.keys - valid_locators).empty?

      case
        when locator[:title]
          find_by_title locator[:title], parent.handle
        when locator[:handle]
          find_by_handle locator[:handle]
        else
          conditions = locator.collect {|k, v|  Library.send("#{k}_condition", v) }
          Library.find_by_conditions parent, scope, *conditions
      end
    end

    private
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
