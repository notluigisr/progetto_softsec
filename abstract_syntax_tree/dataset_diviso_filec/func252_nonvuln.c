bool Item_splocal_row_field::fix_fields(THD *thd, Item **ref)
{
  DBUG_ASSERT(!fixed);
  Item *item= get_variable(thd->spcont)->element_index(m_field_idx);
  return fix_fields_from_item(thd, ref, item);
}