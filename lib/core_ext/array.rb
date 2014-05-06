class Array
  def to_var_args(type)
    self.flatten.reduce([]) { |a, n| a << type << n }
  end
end