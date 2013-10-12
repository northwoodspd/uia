module Uia
  class Element
    def initialize(element)
      @element = element
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