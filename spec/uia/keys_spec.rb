require 'spec_helper'

describe Uia::Keys do
  def encode(*keys)
    Keys.encode keys
  end

  Then { encode('Turd sandwich') == 'Turd sandwich' }
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
    Then { encode('(Turd + sand%wich^ [sweet] {}') == '{(}Turd {+} sand{%}wich{^} {[}sweet{]} {{}{}}' }
  end
end
