class Module
  def const_get_path(path)
    path.split('::').reduce(self) do |m, current|
      m.const_get current.split('_').map(&:capitalize).join
    end
  end
end