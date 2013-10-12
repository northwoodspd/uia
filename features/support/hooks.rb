AfterConfiguration do
  $app = ChildProcess.build('features/support/WindowsForms.exe').start
  sleep 0.5
end

at_exit do
  $app.stop unless $app.exited?
end