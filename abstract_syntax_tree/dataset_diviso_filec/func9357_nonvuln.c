MATCHER_P(HasValue, m, "") {
  if (!arg.has_value()) {
    *result_listener << "STR";
    return false;
  }
  const auto& value = arg.value();
  return ExplainMatchResult(m, value, result_listener);
};