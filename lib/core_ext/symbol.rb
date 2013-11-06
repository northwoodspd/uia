class Symbol
  def to_camelized_s
    self.to_s.split('_').map(&:capitalize).join(' ')
  end

  # :selection_item => Uia::Patterns::SelectionItem
  def to_pattern_const
    "Uia::Patterns::#{self.to_s.capitalize}".split('::').reduce(Object) do |m, current|
      m.const_get current.split('_').map(&:capitalize).join
    end
  end
end