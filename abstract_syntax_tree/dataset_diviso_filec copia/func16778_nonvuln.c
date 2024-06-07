m4_m4wrap (struct obstack *obs, int argc, token_data **argv)
{
  if (bad_argc (argv[0], argc, 2, -1))
    return;
  if (no_gnu_extensions)
    obstack_grow (obs, ARG (1), strlen (ARG (1)));
  else
    dump_args (obs, argc, argv, "STR", false);
  obstack_1grow (obs, '\0');
  push_wrapup ((char *) obstack_finish (obs));
}