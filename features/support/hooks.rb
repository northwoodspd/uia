Before do
  @app = ChildProcess.build('features/support/WindowsForms.exe').start
end

After do
  @app.stop unless @app.exited?
end