# frozen_string_literal: true

require_relative "lib/lazyjson/version"

Gem::Specification.new do |spec|
  spec.name = "lazyjson"
  spec.version = LazyJSON::VERSION
  spec.authors = ["Bo Anderson"]
  spec.email = ["mail@boanderson.me"]

  spec.summary = "Lazy JSON parsing for Ruby using simdjson"
  spec.homepage = "https://github.com/Bo98/lazyjson-ruby"
  spec.license = "BSD-2-Clause"
  spec.required_ruby_version = ">= 3.1.0"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/Bo98/lazyjson-ruby"
  spec.metadata["bug_tracker_uri"] = "https://github.com/Bo98/lazyjson-ruby/issues"
  spec.metadata["changelog_uri"] = "https://github.com/Bo98/lazyjson-ruby/releases/tag/#{spec.version}"
  spec.metadata["rubygems_mfa_required"] = "true"

  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    (Dir.glob("*.{md,txt}") + Dir.glob("{exe,ext,lib,rbi}/**/*")).reject { |f| File.directory?(f) || File.extname(f) == ".#{RbConfig::CONFIG['DLEXT']}" }
  end
  spec.bindir = "exe"
  spec.executables = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions = ["ext/lazyjson/extconf.rb"]

  spec.add_dependency "rice", "~> 4.1"
end
