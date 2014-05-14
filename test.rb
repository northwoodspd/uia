require 'uia'

def w
  @w ||= Uia.find_element title: /^MainForm/
end
