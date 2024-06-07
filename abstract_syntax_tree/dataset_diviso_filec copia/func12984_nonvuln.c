  void pre_next_partition(ha_rows rownum)
  {
    
    peer_tracker.check_if_next_group();
    cursor.on_next_partition(rownum);
    
    add_value_to_items();
  }