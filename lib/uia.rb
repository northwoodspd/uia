require 'uia/version'
require 'uia/library'
require 'uia/library/constants'
require 'uia/element'

module Uia
  class BadLocator < StandardError; end

  def find_element(how)
    case
      when how[:id]
        Library.find_by_id(how[:id])
      when how[:name]
        Library.find_by_name(how[:name])
      when how[:pid]
        Library.find_by_pid(how[:pid])
      when how[:runtime_id]
        Library.find_by_runtime_id(how[:runtime_id])
      when how[:handle]
        Element.new Library.find_by_handle(how[:handle])
      else
        raise BadLocator, "#{how} is not a valid locator"
    end
  end
end
