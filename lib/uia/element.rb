require 'uia/patterns/expand_collapse'
require 'uia/patterns/invoke'
require 'uia/patterns/selection'
require 'uia/patterns/selection_item'
require 'uia/patterns/toggle'
require 'uia/patterns/value'

module Uia
  class Element
    def initialize(element)
      @element = element
      @default = lambda { [:unknown] }
    end

    def control_type
      Library::Constants::ControlTypes.find(@default) { |_, v| v == control_type_id }.first
    end

    def refresh
      Library.refresh @element
      self
    end

    def find(locator)
      case
        when locator[:id]
          Library::find_child_by_id(@element, locator[:id])
        when locator[:name]
          Library::find_child_by_name(@element, locator[:name])
      end
    end

    def as(pattern)
      which =  "Uia::Patterns::#{pattern.to_s.capitalize}".split('::').reduce(Object) do |m, current|
        m.const_get current.split('_').map(&:capitalize).join
      end
      extend which
    end

    def patterns
      pattern_ids.map {|id| Library::Constants::Patterns.find(@default) { |_, v| v == id }.first }
    end

    def children
      @element.children.map { |c| Element.new c }
    end

    def descendants
      @element.descendants.map { |c| Element.new c }
    end

    def click
      Library.click(@element)
      true
    end

    def method_missing(meth, *args, &block)
      if @element.respond_to? meth
        return @element.send(meth, *args, &block)
      end
      super
    end
  end
end