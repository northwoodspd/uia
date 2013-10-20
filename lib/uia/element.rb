module Uia
  class Element
    include Library::Constants

    def initialize(element)
      @element = element
      @default = lambda { [:unknown] }
    end

    def control_type
      ControlTypes.find(@default) { |_, v| v == control_type_id }.first
    end

    def patterns
      pattern_ids.map {|id| Patterns.find(@default) { |_, v| v == id }.first }
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