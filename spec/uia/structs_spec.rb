require 'spec_helper'

include Uia::Library

describe Uia::Library do
  context ElementStruct do
    Given(:element) { ElementCast.new }

    context '#control_type' do
      context 'valid' do
        When { element[:control_type_id] = 50035 }
        Then { element.control_type == :header_item }
      end

      context 'invalid' do
        When { element[:control_type_id] = -1 }
        Then { element.control_type == nil }
      end
    end
  end
end