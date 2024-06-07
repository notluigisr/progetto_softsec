hb_map_create ()
{
  hb_map_t *map;

  if (!(map = hb_object_create<hb_map_t> ()))
    return hb_map_get_empty ();

  map->init_shallow ();

  return map;
}