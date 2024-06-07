Item_func_trig_cond::add_key_fields(JOIN *join, KEY_FIELD **key_fields,
                                    uint *and_level, table_map usable_tables,
                                    SARGABLE_PARAM **sargables)
{
  
  if (!join->group_list && !join->order &&
      join->unit->item && 
      join->unit->item->substype() == Item_subselect::IN_SUBS &&
      !join->unit->is_unit_op())
  {
    KEY_FIELD *save= *key_fields;
    args[0]->add_key_fields(join, key_fields, and_level, usable_tables,
                            sargables);
    
    for (; save != *key_fields; save++)
      save->cond_guard= get_trig_var();
  }
}