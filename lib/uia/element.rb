require 'uia/patterns/value'

module Uia
  class Element
    include Library

    def initialize(element)
      @element = element
      @default = lambda { [:unknown] }
    end

    def control_type
      Constants::ControlTypes.find(@default) { |_, v| v == control_type_id }.first
    end

    def as(pattern)
      which =  "Uia::Patterns::#{pattern.to_s.capitalize}".split('::').reduce(Object) do |m, current|
        m.const_get current
      end
      extend which
    end

    def patterns
      pattern_ids.map {|id| Constants::Patterns.find(@default) { |_, v| v == id }.first }
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