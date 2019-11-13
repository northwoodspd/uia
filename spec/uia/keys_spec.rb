require 'spec_helper'

describe Uia::Keys do
  def encode(*keys)
    Keys.encode keys
  end

  Then { encode('Bacon sandwich') == 'Bacon sandwich' }
  Then { encode([:control, :shift, 'a']) == '^(+a)' }

  context 'special keys' do
    Then { encode(:shift, :f2, :left) == '+{F2}{LEFT}' }
  end

  context 'special characters' do
    Then { encode('1 + 2') == '1 {+} 2' }
    Then { encode('1 ^^ 2') == '1 {^}{^} 2' }
    Then { encode('a%b') == 'a{%}b' }
    Then { encode('~ish') == '{~}ish' }
    Then { encode('(1 - 2)') == '{(}1 - 2{)}' }
    Then { encode('{DUDE}') == '{{}DUDE{}}' }
    Then { encode('[DUDE]') == '{[}DUDE{]}' }
    Then { encode('(Bacon + sand%wich^ [sweet] {}') == '{(}Bacon {+} sand{%}wich{^} {[}sweet{]} {{}{}}' }
  end

  context 'invalid' do
    When(:bad_keys) { encode('something', :bad_key) }
    Then { expect(bad_keys).to have_failed InvalidKey, "#{:bad_key} is not a valid key" }
  end
end
