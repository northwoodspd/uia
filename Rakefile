require 'bundler/setup'
require 'bundler/gem_tasks'
require 'rspec/core/rake_task'

require 'albacore'
require 'albacore/tasks/versionizer'

RSpec::Core::RakeTask.new(:spec)

task :default => :spec

task :spec => [:build_release, :build_release_x64]
task :build => :spec

desc 'Build the release version of UiaDll'
build :build_release do |b|
  b.sln = 'ext/UiaDll/UiaDll.sln'
  b.prop :Platform, 'Mixed Platforms'
  b.prop :Configuration, :Release
end

desc 'Build the release x64 version of UiaDll'
build :build_release_x64 do |b|
  b.sln = 'ext/UiaDll/UiaDll.sln'
  b.prop :Platform, 'Mixed Platforms'
  b.prop :Configuration, 'Release x64'
end
