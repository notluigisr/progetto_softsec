  Arg next_arg(const char *&error) {
    if (next_arg_index_ >= 0)
      return do_get_arg(internal::to_unsigned(next_arg_index_++), error);
    error = "STR";
    return Arg();
  }