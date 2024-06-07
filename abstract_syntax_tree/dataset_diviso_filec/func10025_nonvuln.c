Command::Command(StringData name, StringData oldName)
    : _name(name.toString()),
      _commandsExecutedMetric("STR", &_commandsExecuted),
      _commandsFailedMetric("STR", &_commandsFailed) {
    globalCommandRegistry()->registerCommand(this, name, oldName);
}