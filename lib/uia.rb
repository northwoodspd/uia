require 'require_all'
require 'uia/version'
require 'uia/library'
require 'uia/library/constants'
require 'uia/finder'
require 'uia/element'

require_rel 'uia/patterns'
require_rel 'core_ext'

module Uia
  class BadLocator < StandardError; end
  extend Finder

  def self.children
    Library.root_children
  end

  def self.find_element(how)
    case
      when how[:id]
        find_by_id how[:id]
      when how[:name]
        find_by_name how[:name]
      when how[:pid]
        find_by_pid how[:pid]
      when how[:runtime_id]
        find_by_runtime_id how[:runtime_id]
      when how[:handle]
        find_by_handle how[:handle]
      else
        raise BadLocator, "#{how} is not a valid locator"
    end
  end
end
