require 'uia/library/element_attributes'
require 'uia/library/pattern_info_attributes'
require 'uia/keys'

module Uia
  class UnsupportedPattern < StandardError
    def initialize(expected, actual)
      super "Pattern #{expected} not found in #{actual}"
    end
  end

  class Element
    include Finder
    extend ElementAttributes

    def initialize(element)
      @element = element
      @default = lambda { [:unknown] }
    end

    element_attr :id, :name, :handle, :runtime_id,
                 :class_name, :children, :descendants
    refreshed_element_attr :enabled?, :visible?, :focused?, :bounding_rectangle

    def control_type
      Library::Constants::ControlTypes.find(@default) { |_, v| v == @element.control_type_id }.first
    end

    def drag(info)
      start_x, start_y = info[:start]
      end_x, end_y = info[:end]
      left, top = bounding_rectangle

      coords = [
          left + start_x,
          top + start_y,
          left + end_x,
          top + end_y
      ]

      until focused?
        focus
      end
      Library.drag *coords
    end

    def send_keys(*keys)
      Library.send_keys @element, Keys.encode(keys)
    end

    def refresh
      Library.refresh @element
      self
    end

    def find(locator)
      find_child(@element, locator)
    end

    def locators_match?(locator)
      locator.all? do |locator, value|
        case locator
          when :pattern
            case value
              when Array
                !(patterns & value).empty?
              else
                patterns.include? value
            end
          else
            case value
              when Array
                value.include? send(locator)
              else
                send(locator) == value
            end
        end
      end
    end

    def filter(locator)
      descendants.select { |e| e.locators_match? locator }
    end

    def as(pattern)
      raise UnsupportedPattern.new(pattern, patterns) unless patterns.include? pattern
      extend pattern.to_pattern_const
    end

    def patterns
      @element.pattern_ids.map { |id| Library::Constants::Patterns.find(@default) { |_, v| v == id }.first }
    end

    def click
      Library.click(@element)
      true
    end

    def click_center
      Library.click_center(@element)
      true
    end

    def focus
      Library.focus(@element)
    end
  end
end