class Symbol
  def to_camelized_s
    self.to_s.split('_').map(&:capitalize).join(' ')
  end

  def to_pattern_available_property
    "Is#{self.to_camelized_s.delete(' ')}PatternAvailableProperty"
  end

  # :selection_item => Uia::Patterns::SelectionItem
  def to_pattern_const
    Uia::Patterns.const_get_path "#{self.capitalize}"
  end

  def to_control_type
    Uia::ControlTypes.const_get_path "#{self.capitalize}"
  end

  def to_control_type_const
    control_type = Uia::Library::Constants::ControlTypes[self]
    raise Uia::InvalidControlType.new(self) unless control_type
    control_type
  end
end