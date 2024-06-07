std::ostream& operator<<(std::ostream& out, HealthTransition changed_state) {
  switch (changed_state) {
  case HealthTransition::Unchanged:
    out << "STR";
    break;
  case HealthTransition::Changed:
    out << "STR";
    break;
  case HealthTransition::ChangePending:
    out << "STR";
    break;
  }
  return out;
}