get_group_list (ngp)
     int *ngp;
{
  static char **group_vector = (char **)NULL;
  register int i;

  if (group_vector)
    {
      if (ngp)
	*ngp = ngroups;
      return group_vector;
    }

  if (ngroups == 0)
    initialize_group_array ();

  if (ngroups <= 0)
    {
      if (ngp)
	*ngp = 0;
      return (char **)NULL;
    }

  group_vector = strvec_create (ngroups);
  for (i = 0; i < ngroups; i++)
    group_vector[i] = itos (group_array[i]);

  if (ngp)
    *ngp = ngroups;
  return group_vector;
}