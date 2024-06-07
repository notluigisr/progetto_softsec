hb_ot_layout_table_get_lookup_count (hb_ot_layout_t            *layout,
				     hb_ot_layout_table_type_t  table_type)
{
  const GSUBGPOS &g = get_gsubgpos_table (layout, table_type);

  return g.get_lookup_count ();
}