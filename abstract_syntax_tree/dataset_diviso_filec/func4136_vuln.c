static inline int parse_value_and_bound(const string &input, long *output, const long lower_bound, const long upper_bound, const long default_val)
{
  if (!input.empty()) {
    char *endptr;
    *output = strtol(input.c_str(), &endptr, 10);
    if (endptr) {
      if (endptr == input.c_str()) return -EINVAL;
      while (*endptr && isspace(*endptr)) 
        endptr++;
      if (*endptr) {
        return -EINVAL;
      }
    }
    if(*output > upper_bound) {
      *output = upper_bound;
    }
    if(*output < lower_bound) {
      *output = lower_bound;
    }
  } else {
    *output = default_val;
  }

  return 0;
}