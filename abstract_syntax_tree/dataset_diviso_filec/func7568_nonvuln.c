hb_map_destroy (hb_map_t *map)
{
  if (!hb_object_destroy (map)) return;

  map->fini_shallow ();

  hb_free (map);
}