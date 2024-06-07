  Field_short(uchar *ptr_arg, uint32 len_arg, uchar *null_ptr_arg,
	      uchar null_bit_arg,
	      enum utype unireg_check_arg, const LEX_CSTRING *field_name_arg,
	      bool zero_arg, bool unsigned_arg)
    :Field_int(ptr_arg, len_arg, null_ptr_arg, null_bit_arg,
               unireg_check_arg, field_name_arg, zero_arg, unsigned_arg)
    {}