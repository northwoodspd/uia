require 'require_all'
require 'uia/version'
require 'uia/library'
require 'uia/library/constants'
require 'uia/finder'
require 'uia/element'

require_rel 'uia/patterns'
require_rel 'uia/control_types'
require_rel 'core_ext'

module Uia
  extend Finder

  def self.children
    Library.root_children
  end

  def self.find_element(how)
    find_from_root(how)
  end
end
