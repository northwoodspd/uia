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

# returns all elements under main_window that are of control type button
main_window.select(control_type: :button)

# returns the values of every element that implements the ValuePattern
main_window.select(pattern: :value).map {|e| e.as :value}.map &:value
```

### Finding Elements

You can locate elements based on the following criteria:

* `:id`         - find by their `AutomationId` (`String` and `Regexp`)
* `:pid`        - find an element by their process id  (`String` and `Regexp`)
* `:handle`     - find an element by their native window handle (`Fixnum`)
* `:runtime_id` - find an element by their `RuntimeId` (i.e. `[42, 12345]`)

### `Element`
The `Element` class is a representation of the [`AutomationElement`](http://msdn.microsoft.com/en-us/library/system.windows.automation.automationelement.aspx) class in Microsoft UIA. It is the object that is returned from the root `Uia#find_element` as well as the `Element#find` and `Element#select` methods.

#### Properties

*  `id` - returns the automation id of th element
*  `name` - returns the name of the element
*  `handle` - returns the native window handle of the element
*  `class_name` - returns the class name of the element
*  `patterns` - returns the patterns that element implements (i.e. `[:window, :transform]`)

#### Methods

##### #as
The `#as` method will decorate the `Element` with the specific pattern that you would like to interact with.

```ruby
button = Uia.find_element(id: /MainForm/).find(id: 'aboutButton').as :invoke
button.invoke
```

### Patterns
#### Window
Decorates your `Element` with the following methods:
*  `visual_state` - `:minimized, :maximized, :normal`
*  `visual_state=` - sets the visual state
*  `can_minimize?` / `can_maximize?`
*  `modal?`
*  `topmost?`
*  `interaction_state` - `:blocked_by_modalwindow, :closing, :not_responding, :ready_for_user_interaction, :running`

#### Value
*  `value` - returns the value
*  `value=` - sets the value
*  `read_only?`

#### Invoke
*  `invoke` - invokes the control

#### ExpandCollapse
*  `expand` - expands the element
*  `collapse` - collapses the element
*  `expand_collapse_state` - `:collapsed, :expanded, :leaf_node, :partially_expanded`

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
