bool SQLiteDBManager::isDisabled(const std::string& table_name) {
  bool disabled_set = !Flag::isDefault("STR");
  bool enabled_set = !Flag::isDefault("STR");
  if (!disabled_set && !enabled_set) {
    
    
    return false;
  }
  const auto& element_disabled = instance().disabled_tables_.find(table_name);
  const auto& element_enabled = instance().enabled_tables_.find(table_name);
  bool table_disabled = (element_disabled != instance().disabled_tables_.end());
  bool table_enabled = (element_enabled != instance().enabled_tables_.end());

  if (table_disabled) {
    return true;
  }

  if (table_enabled && disabled_set && !table_disabled) {
    return false;
  }

  if (table_enabled && !disabled_set) {
    return false;
  }

  if (enabled_set && !table_enabled) {
    return true;
  }

  if (disabled_set && !table_disabled) {
    return false;
  }

  return true;
}