require 'uia/library/element_attributes'
require 'uia/library/pattern_info_attributes'

module Uia
  class UnsupportedPattern < StandardError
    def initialize(expected, actual)
      super "Pattern #{expected} not found in #{actual}"
    end
  end

  class Element
    extend ElementAttributes

    def initialize(element)
      @element = element
      @default = lambda { [:unknown] }
    end

    element_attr :id, :name, :handle, :runtime_id,
                 :class_name, :children, :descendants
    refreshed_element_attr :enabled?, :visible?

    def control_type
      Library::Constants::ControlTypes.find(@default) { |_, v| v == @element.control_type_id }.first
    end

    def send_keys(keys_to_send)
      Library.send_keys @element, keys_to_send
    end

    def refresh
      Library.refresh @element
      self
    end

    def find(locator)
      scope = (locator[:scope] || :descendants).to_s.capitalize

      case
        when locator[:id]
          Library::find_child_by_id(@element, locator[:id], scope)
        when locator[:name]
          Library::find_child_by_name(@element, locator[:name], scope)
      end
    end

    def locators_match?(locator)
      locator.all? do |locator, value|
        case locator
          when :pattern
            patterns.include? value
          else
            send(locator) == value
        end
      end
    end

    def select(locator)
      descendants.select { |e| e.locators_match? locator }
    end

    def as(pattern)
      raise UnsupportedPattern.new(pattern, patterns) unless patterns.include? pattern

      which = "Uia::Patterns::#{pattern.to_s.capitalize}".split('::').reduce(Object) do |m, current|
        m.const_get current.split('_').map(&:capitalize).join
      end
      extend which
    end

    def patterns
      @element.pattern_ids.map { |id| Library::Constants::Patterns.find(@default) { |_, v| v == id }.first }
    end

    def click
      Library.click(@element)
      true
    end
  end
end