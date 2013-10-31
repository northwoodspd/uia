class String
  def to_snake_case_sym
    self.gsub(/(.)([A-Z])/, '\1_\2').downcase.to_sym
  end
end