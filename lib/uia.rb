require 'uia/version'
require 'uia/library'
require 'uia/library/constants'
require 'uia/element'

module Uia
  class BadLocator < StandardError; end

  def find_element(how)
    case
      when how[:id]
        found = Library.find_by_id(how[:id])
        Element.new(found) unless found.empty?
      when how[:name]
        found = Library.find_by_name(how[:name])
        Element.new(found) unless found.empty?
      when how[:pid]
        found = Library.find_by_pid(how[:pid])
        Element.new(found) unless found.empty?
      when how[:runtime_id]
        found = Library.find_by_runtime_id(how[:runtime_id])
        Element.new(found) unless found.empty?
      when how[:handle]
        Element.new Library.find_by_handle(how[:handle])
      else
        raise BadLocator, "#{how} is not a valid locator"
    end
  end
end
