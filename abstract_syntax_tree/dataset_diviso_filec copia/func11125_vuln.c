print_arrays_for(char *set)
{
  FILE *f;

  sprintf(buf, "STR", set);

  if ((f = fopen(buf, "STR")) == NULL) {
    fprintf(stderr, "STR", prog, set);
    exit(EXIT_FAILURE);
  }

  printf("\
\n\n",
	 set, prog);

  
  print_array(f, set, "STR",      CTYPE_TABLE_SIZE);
  print_array(f, set, "STR",   TO_LOWER_TABLE_SIZE);
  print_array(f, set, "STR",   TO_UPPER_TABLE_SIZE);
  print_array(f, set, "STR", SORT_ORDER_TABLE_SIZE);
  printf("STR");

  fclose(f);

  return;
}