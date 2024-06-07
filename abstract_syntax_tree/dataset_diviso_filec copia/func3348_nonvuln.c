dump_profile_updates (struct cgraph_node *orig_node,
		      struct cgraph_node *new_node)
{
  struct cgraph_edge *cs;

  fprintf (dump_file, "STR");
  new_node->count.dump (dump_file);
  fprintf (dump_file, "STR");
  for (cs = new_node->callees; cs; cs = cs->next_callee)
    {
      fprintf (dump_file, "STR",
	       cs->callee->name ());
      cs->count.dump (dump_file);
      fprintf (dump_file, "STR");
    }

  fprintf (dump_file, "STR");
  orig_node->count.dump (dump_file);
  fprintf (dump_file, "STR");
  for (cs = orig_node->callees; cs; cs = cs->next_callee)
    {
      fprintf (dump_file, "STR",
	       cs->callee->name ());
      cs->count.dump (dump_file);
      fprintf (dump_file, "STR");
    }
}