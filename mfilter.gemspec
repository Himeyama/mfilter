# frozen_string_literal: true

require_relative "lib/mfilter/version"

Gem::Specification.new do |spec|
  spec.name          = "mfilter"
  spec.version       = Mfilter::VERSION
  spec.authors       = ["Murata Mitsuharu"]
  spec.email         = ["hikari.photon+dev@gmail.com"]

  spec.summary       = "Matlab filter function compatibility."
  spec.required_ruby_version = Gem::Requirement.new(">= 2.3.0")
  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{\A(?:test|spec|features)/}) }
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{\Aexe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib", "ext"]
  spec.extensions    = ["ext/mfilter/extconf.rb"]

  spec.add_development_dependency "rake", ">= 12.3.3"
  spec.add_development_dependency "rake-compiler", "~> 1.1.1"
end
