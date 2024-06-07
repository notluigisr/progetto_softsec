  Field_timestamp_hires(uchar *ptr_arg,
                        uchar *null_ptr_arg, uchar null_bit_arg,
                        enum utype unireg_check_arg,
                        const LEX_CSTRING *field_name_arg,
                        TABLE_SHARE *share, uint dec_arg) :
  Field_timestamp_with_dec(ptr_arg, null_ptr_arg, null_bit_arg,
                           unireg_check_arg, field_name_arg, share, dec_arg)
  {
    DBUG_ASSERT(dec);
  }