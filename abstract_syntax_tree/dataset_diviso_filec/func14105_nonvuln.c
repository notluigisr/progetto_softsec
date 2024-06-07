void TABLE::mark_columns_needed_for_update()
{
  DBUG_ENTER("STR");
  bool need_signal= false;

  mark_columns_per_binlog_row_image();

  if (triggers)
    triggers->mark_fields_used(TRG_EVENT_UPDATE);
  if (default_field)
    mark_default_fields_for_write(FALSE);
  if (vfield)
    need_signal|= mark_virtual_columns_for_write(FALSE);
  if (file->ha_table_flags() & HA_REQUIRES_KEY_COLUMNS_FOR_DELETE)
  {
    KEY *end= key_info + s->keys;
    for (KEY *k= key_info; k < end; k++)
    {
      KEY_PART_INFO *kpend= k->key_part + k->ext_key_parts;
      int any_written= 0, all_read= 1;
      for (KEY_PART_INFO *kp= k->key_part; kp < kpend; kp++)
      {
        int idx= kp->fieldnr - 1;
        any_written|= bitmap_is_set(write_set, idx);
        all_read&= bitmap_is_set(read_set, idx);
      }
      if (any_written && !all_read)
      {
        for (KEY_PART_INFO *kp= k->key_part; kp < kpend; kp++)
        {
          int idx= kp->fieldnr - 1;
          if (bitmap_fast_test_and_set(read_set, idx))
            continue;
          if (field[idx]->vcol_info)
            mark_virtual_col(field[idx]);
        }
      }
    }
    need_signal= true;
  }
  else
  {
    if (found_next_number_field)
      mark_auto_increment_column();
  }

  if (file->ha_table_flags() & HA_PRIMARY_KEY_REQUIRED_FOR_DELETE)
  {
    
    if (s->primary_key == MAX_KEY)
      file->use_hidden_primary_key();
    else
    {
      mark_index_columns_for_read(s->primary_key);
      need_signal= true;
    }
  }
  if (s->versioned)
  {
    
    bitmap_union(read_set, &s->all_set);
    need_signal= true;
  }
  if (check_constraints)
  {
    mark_check_constraint_columns_for_read();
    need_signal= true;
  }

  
  if ((file->ha_table_flags() & HA_PARTIAL_COLUMN_READ) &&
      default_field && s->has_update_default_function)
  {
    bitmap_union(read_set, write_set);
    need_signal= true;
  }
  if (need_signal)
    file->column_bitmaps_signal();
  DBUG_VOID_RETURN;
}