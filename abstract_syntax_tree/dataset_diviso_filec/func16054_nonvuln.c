bool TABLE::add_tmp_key(uint key, uint key_parts,
                        uint (*next_field_no) (uchar *), uchar *arg,
                        bool unique)
{
  DBUG_ASSERT(key < max_keys);

  char buf[NAME_CHAR_LEN];
  KEY* keyinfo;
  Field **reg_field;
  uint i;

  bool key_start= TRUE;
  KEY_PART_INFO* key_part_info=
      (KEY_PART_INFO*) alloc_root(&mem_root, sizeof(KEY_PART_INFO)*key_parts);
  if (!key_part_info)
    return TRUE;
  keyinfo= key_info + key;
  keyinfo->key_part= key_part_info;
  keyinfo->usable_key_parts= keyinfo->user_defined_key_parts = key_parts;
  keyinfo->ext_key_parts= keyinfo->user_defined_key_parts;
  keyinfo->key_length=0;
  keyinfo->algorithm= HA_KEY_ALG_UNDEF;
  keyinfo->flags= HA_GENERATED_KEY;
  keyinfo->ext_key_flags= keyinfo->flags;
  keyinfo->is_statistics_from_stat_tables= FALSE;
  if (unique)
    keyinfo->flags|= HA_NOSAME;
  sprintf(buf, "STR", key);
  if (!(keyinfo->name= strdup_root(&mem_root, buf)))
    return TRUE;
  keyinfo->rec_per_key= (ulong*) alloc_root(&mem_root,
                                            sizeof(ulong)*key_parts);
  if (!keyinfo->rec_per_key)
    return TRUE;
  bzero(keyinfo->rec_per_key, sizeof(ulong)*key_parts);
  keyinfo->read_stats= NULL;
  keyinfo->collected_stats= NULL;

  for (i= 0; i < key_parts; i++)
  {
    uint fld_idx= next_field_no(arg); 
    reg_field= field + fld_idx;
    if (key_start)
      (*reg_field)->key_start.set_bit(key);
    (*reg_field)->part_of_key.set_bit(key);
    create_key_part_by_field(key_part_info, *reg_field, fld_idx+1);
    keyinfo->key_length += key_part_info->store_length;
    (*reg_field)->flags|= PART_KEY_FLAG;
    key_start= FALSE;
    key_part_info++;
  }

  set_if_bigger(s->max_key_length, keyinfo->key_length);
  s->keys++;
  return FALSE;
}