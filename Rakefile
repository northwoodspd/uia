require 'bundler/setup'
require 'bundler/gem_tasks'
require 'rspec/core/rake_task'

RSpec::Core::RakeTask.new(:spec)

task :default => :spec
task :spec => :build_release
task :build => :spec

desc 'Build the release version of UiaDll'
task :build_release do
  Dir.chdir('ext/UiaDll') do
    if !system('msbuild UiaDll.sln -target:Rebuild -property:Configuration=Release')
      fail "Failed to build UiaDll: #{$?.exitstatus}"
    end
  end
end
