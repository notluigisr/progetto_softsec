std::function<bool(T, T)> GetComparefunction(bool is_arg_max) {
  if (is_arg_max) {
    return std::greater<T>();
  } else {
    return std::less<T>();
  }
}