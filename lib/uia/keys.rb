module Uia
  class InvalidKey < StandardError; end
  class Keys
    # http://msdn.microsoft.com/en-us/library/system.windows.forms.sendkeys(v=vs.110).aspx
    KEYS = {
        :shift => '+',
        :control => '^',
        :alt => '%',
        :space => ' ',
        :backspace => '{BS}',
        :break => '{BREAK}',
        :caps_lock => '{CAPSLOCK}',
        :delete => '{DEL}',
        :down => '{DOWN}',
        :end => '{END}',
        :enter => '{ENTER}',
        :escape => '{ESC}',
        :help => '{HELP}',
        :home => '{HOME}',
        :insert => '{INS}',
        :left => '{LEFT}',
        :number_lock => '{NUMLOCK}',
        :page_down => '{PGDN}',
        :page_up => '{PGUP}',
        :print_screen => '{PRTSC}',
        :right => '{RIGHT}',
        :scroll_lock => '{SCROLLLOCK}',
        :tab => '{TAB}',
        :up => '{UP}',
        :f1 => '{F1}',
        :f2 => '{F2}',
        :f3 => '{F3}',
        :f4 => '{F4}',
        :f5 => '{F5}',
        :f6 => '{F6}',
        :f7 => '{F7}',
        :f8 => '{F8}',
        :f9 => '{F9}',
        :f10 => '{F10}',
        :f11 => '{F11}',
        :f12 => '{F12}',
        :f13 => '{F13}',
        :f14 => '{F14}',
        :f15 => '{F15}',
        :f16 => '{F16}',
        :add => '{ADD}',
        :subtract => '{SUBTRACT}',
        :multiply => '{MULTIPLY}',
        :divide => '{DIVIDE}'}

    SPECIAL_KEYS = ['\+', '\^', '%', '~', '\(', '\)', '\{', '\}', '\[', '\]']

    def self.encode(keys)
      keys.reduce('') do |encoded, key|
        encoded << case key
                     when String
                       encode_str(key)
                     when Symbol
                       encode_sym(key)
                     when Array
                       "#{encode([key.shift])}(#{encode(key)})"
                   end
      end
    end

    def self.encode_str(s)
      s.gsub(/([#{SPECIAL_KEYS.join ''}])/, '{\1}')
    end

    def self.encode_sym(sym)
      found = KEYS[sym]
      raise InvalidKey, "#{sym} is not a valid key" unless found
      found
    end
  end
end