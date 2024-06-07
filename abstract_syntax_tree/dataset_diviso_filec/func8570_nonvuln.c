char *
sub_append_number (number, target, indx, size)
     intmax_t number;
     char *target;
     int *indx;
     size_t *size;
{
  char *temp;

  temp = itos (number);
  return (sub_append_string (temp, target, indx, size));