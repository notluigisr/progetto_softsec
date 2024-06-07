  void set_type(const Column_definition &other)
  {
    set_handler(other.type_handler());
    length= other.length;
    char_length= other.char_length;
    decimals= other.decimals;
    flags= other.flags;
    pack_length= other.pack_length;
    key_length= other.key_length;
    unireg_check= other.unireg_check;
    interval= other.interval;
    charset= other.charset;
    srid= other.srid;
    geom_type= other.geom_type;
    pack_flag= other.pack_flag;
  }