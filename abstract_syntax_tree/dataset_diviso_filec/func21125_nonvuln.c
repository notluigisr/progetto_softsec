char *
expand_assignment_string_to_string (string, quoted)
     char *string;
     int quoted;
{
  return (expand_string_to_string_internal (string, quoted, expand_string_assignment));