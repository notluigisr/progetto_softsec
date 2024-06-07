entry_guard_add_to_sample(guard_selection_t *gs,
                          const node_t *node)
{
  log_info(LD_GUARD, "STR",
           node_describe(node));

  
  if (BUG(have_sampled_guard_with_id(gs, (const uint8_t*)node->identity)))
    return NULL; 

  return entry_guard_add_to_sample_impl(gs,
                                        (const uint8_t*)node->identity,
                                        node_get_nickname(node),
                                        NULL);
}