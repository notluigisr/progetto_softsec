void ha_myisam::update_create_info(HA_CREATE_INFO *create_info)
{
  ha_myisam::info(HA_STATUS_AUTO | HA_STATUS_CONST);
  if (!(create_info->used_fields & HA_CREATE_USED_AUTO))
  {
    create_info->auto_increment_value= stats.auto_increment_value;
  }
  create_info->data_file_name=data_file_name;
  create_info->index_file_name=index_file_name;
}