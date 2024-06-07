  void next_partition(ha_rows rownum)
  {
    cursor.move_to(rownum);
    walk_till_non_peer();
  }