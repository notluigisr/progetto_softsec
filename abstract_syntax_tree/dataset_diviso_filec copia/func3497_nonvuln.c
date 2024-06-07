  void set_storage_type(ha_storage_media storage_type_arg)
  {
    DBUG_ASSERT(field_storage_type() == HA_SM_DEFAULT);
    flags |= static_cast<uint32>(storage_type_arg) <<
      FIELD_FLAGS_STORAGE_MEDIA;
  }