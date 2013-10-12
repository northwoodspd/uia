Then(/^we can find the element with id "([^"]*)"$/) do |id|
  expect(find_element(id: id)).to_not be_nil
end