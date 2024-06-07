void Column_definition::create_length_to_internal_length(void)
{
  switch (sql_type) {
  case MYSQL_TYPE_TINY_BLOB:
  case MYSQL_TYPE_MEDIUM_BLOB:
  case MYSQL_TYPE_LONG_BLOB:
  case MYSQL_TYPE_BLOB:
  case MYSQL_TYPE_GEOMETRY:
  case MYSQL_TYPE_VAR_STRING:
  case MYSQL_TYPE_STRING:
  case MYSQL_TYPE_VARCHAR:
    length*= charset->mbmaxlen;
    set_if_smaller(length, UINT_MAX32);
    key_length= (uint32)length;
    pack_length= calc_pack_length(sql_type, key_length);
    break;
  case MYSQL_TYPE_ENUM:
  case MYSQL_TYPE_SET:
    
    length*= charset->mbmaxlen;
    key_length= pack_length;
    break;
  case MYSQL_TYPE_BIT:
    if (f_bit_as_char(pack_flag))
    {
      key_length= pack_length= ((length + 7) & ~7) / 8;
    }
    else
    {
      pack_length= (uint)(length / 8);
      
      key_length= pack_length + MY_TEST(length & 7);
    }
    break;
  case MYSQL_TYPE_NEWDECIMAL:
  {
    
    uint precision= my_decimal_length_to_precision((uint)length, decimals,
                                                   flags & UNSIGNED_FLAG);
    set_if_smaller(precision, DECIMAL_MAX_PRECISION);
    key_length= pack_length= my_decimal_get_binary_size(precision, decimals);
    break;
  }
  default:
    key_length= pack_length= calc_pack_length(sql_type, (uint)length);
    break;
  }
}