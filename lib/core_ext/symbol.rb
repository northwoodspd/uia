class Symbol
  def to_camelized_s
    self.to_s.split('_').map(&:capitalize).join(' ')
  end
end