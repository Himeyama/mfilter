# Mfilter
[![Gem Version](https://badge.fury.io/rb/mfilter.svg)](https://badge.fury.io/rb/mfilter)

MatLab (Octave) ライクの `filter` 関数の Ruby 実装。

## インストール方法

> インストールが必要なパッケージ
```sh
sudo apt update
sudo apt install liboctave-dev -y

# or

brew install octave
```

> Gemfile
```ruby
gem "mfilter"
```

Gem のインストールを実行:

    $ bundle install

> Gem のインストール

    $ gem install mfilter

## 使用例
```ruby
#!/usr/bin/env ruby

require "mfilter"

t = Array.new(100){|i| -Math::PI + i * 2 * Math::PI / (100 - 1)}
x = t.map{|e| Math::sin(e) + 0.25 * rand}
b = [0.2] * 5
a = [1]

y = MFilter::filter(b, a, x)

open("test/data.dat", "w") do |f|
    f.puts [t, x, y].transpose.map{|e| e.join(" ")}
end
```

![example](https://user-images.githubusercontent.com/39254183/130913789-0245fa7f-1537-456c-8669-58ef9d9ab89c.png)



## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/himeyama/mfilter.
