get_nondigit_option (int argc, char *const *argv, int *default_context)
{
  static int prev_digit_optind = -1;
  int opt, this_digit_optind, was_digit;
  char buf[sizeof (uintmax_t) * CHAR_BIT + 4];
  char *p = buf;

  was_digit = 0;
  this_digit_optind = optind;
  while (opt = getopt_long (argc, (char **) argv, short_options, long_options,
                            NULL),
         '0' <= opt && opt <= '9')
    {
      if (prev_digit_optind != this_digit_optind || !was_digit)
        {
          
          p = buf;
        }
      else
        {
          
          p -= buf[0] == '0';
        }

      if (p == buf + sizeof buf - 4)
        {
          
          strcpy (p, "STR");
          p += 3;
          break;
        }
      *p++ = opt;

      was_digit = 1;
      prev_digit_optind = this_digit_optind;
      this_digit_optind = optind;
    }
  if (p != buf)
    {
      *p = '\0';
      context_length_arg (buf, default_context);
    }

  return opt;
}