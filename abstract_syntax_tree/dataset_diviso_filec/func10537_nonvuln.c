entry_guards_free_all(void)
{
  
  curr_guard_context = NULL;
  
  if (guard_contexts != NULL) {
    SMARTLIST_FOREACH_BEGIN(guard_contexts, guard_selection_t *, gs) {
      guard_selection_free(gs);
    } SMARTLIST_FOREACH_END(gs);
    smartlist_free(guard_contexts);
    guard_contexts = NULL;
  }
  circuit_build_times_free_timeouts(get_circuit_build_times_mutable());
}