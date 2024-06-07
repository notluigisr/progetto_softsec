static void print_help()
{
  MEM_ROOT mem_root;
  init_alloc_root(&mem_root, 4096, 4096);

  pop_dynamic(&all_options);
  sys_var_add_options(&all_options, sys_var::PARSE_EARLY);
  add_plugin_options(&all_options, &mem_root);
  sort_dynamic(&all_options, (qsort_cmp) option_cmp);
  add_terminator(&all_options);

  my_print_help((my_option*) all_options.buffer);
  my_print_variables((my_option*) all_options.buffer);

  free_root(&mem_root, MYF(0));
}