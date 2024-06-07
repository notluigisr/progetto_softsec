queue_ref_for_analysis (FlatpakDecomposed *ref,
                        const char *arch,
                        GHashTable *analyzed_refs,
                        GQueue     *refs_to_analyze)
{
  if (arch != NULL && !flatpak_decomposed_is_arch (ref, arch))
    return;

  if (g_hash_table_lookup (analyzed_refs, ref) != NULL)
    return;

  g_hash_table_add (analyzed_refs, flatpak_decomposed_ref (ref));
  g_queue_push_tail (refs_to_analyze, ref); 
}