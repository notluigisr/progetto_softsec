int
do_assignment (string)
     char *string;
{
  WORD_DESC td;

  td.flags = W_ASSIGNMENT;
  td.word = string;

  return do_assignment_internal (&td, 1);