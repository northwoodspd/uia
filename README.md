# Uia

The `Uia` gem is a low-level driver for interacting with Microsoft UIA elements in a Windows environment.

## Installation

Add this line to your application's Gemfile:

    gem 'uia'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install uia

## Usage

Getting started with `uia` is easy. Simply require `uia` and then include the `Uia` module wherever you would like to use it.

```ruby
require 'uia'

include Uia

main_window = find_element id: 'MainFormWindow'
```

### Finding Elements

You can locate elements based on the following criteria:

* `:id`         - find by their `AutomationId`
* `:pid`        - find an element by their process id
* `:handle`     - find an element by their native window handle
* `:runtime_id` - find an element by their `RuntimeId` (i.e. `[42, 12345]`)

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
