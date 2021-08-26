# Mfilter
MatLab (Octave) ライクの `filter` 関数の Ruby 実装。

## インストール方法

### 依存
- liboctave.so
- liboctinterp.so

```ruby
gem "mfilter", github: "himeyama/mfilter.git", branch: :main
```

Gem のインストールを実行:

    $ bundle install

または、

    $ gem install specific_install
    $ gem specific_install -l "himeyama/mfilter.git"

## 使用法

```ruby
require "mfilter"
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/himeyama/mfilter.
