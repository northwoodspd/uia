Then(/^we can find the element with id "([^"]*)"$/) do |id|
  expect(find_element(id: id)).to_not be_nil
end

Then(/^we can find elements by process id$/) do
  expect(find_element(pid: $app.pid)).to_not be_nil
end

Then(/^we can find elements by their runtime id$/) do
  runtime_id = find_element(pid: $app.pid).runtime_id
  expect(find_element(runtime_id: runtime_id)).to_not be_nil
end

Then(/^we can find elements by their window handle$/) do
  handle = find_element(pid: $app.pid).handle
  expect(find_element(handle: handle)).to_not be_nil
end

When(/^we cannot find elements by the "([^"]*)" locator$/) do |locator|
  h = {locator.to_sym => 123}
  expect { find_element(h) }.to raise_error("#{h} is not a valid locator")
end