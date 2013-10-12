Feature:  Finding with elements

  Scenario: Finding by id
    Then we can find the element with id "MainFormWindow"

  Scenario: Finding by process id
    Then we can find elements by process id

  Scenario: Finding by runtime id
    Then we can find elements by their runtime id

  Scenario: Finding by their window handle
    Then we can find elements by their window handle

  Scenario: Any other locator is invalid
    But we cannot find elements by the "invalid" locator