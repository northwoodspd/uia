module Uia
  module Finder
    def find_by_id(id)
      Library.find_by_id(id)
    end

    def find_by_name(name)
      Library.find_by_name(name)
    end

    def find_by_pid(pid)
      Library.find_by_pid(pid)
    end

    def find_by_runtime_id(runtime_id)
      Library.find_by_runtime_id(runtime_id)
    end

    def find_by_handle(handle)
      Library.find_by_handle handle
    end
  end
end
