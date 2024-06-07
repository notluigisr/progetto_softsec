void mi_disable_non_unique_index(MI_INFO *info, ha_rows rows)
{
  MYISAM_SHARE *share=info->s;
  MI_KEYDEF    *key=share->keyinfo;
  uint          i;

  DBUG_ASSERT(info->state->records == 0 &&
              (!rows || rows >= MI_MIN_ROWS_TO_DISABLE_INDEXES));
  for (i=0 ; i < share->base.keys ; i++,key++)
  {
    if (!(key->flag & (HA_NOSAME | HA_SPATIAL | HA_AUTO_KEY)) &&
        ! mi_too_big_key_for_sort(key,rows) && info->s->base.auto_key != i+1)
    {
      mi_clear_key_active(share->state.key_map, i);
      info->update|= HA_STATE_CHANGED;
    }
  }
}