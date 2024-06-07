  Field_long(uint32 len_arg,bool maybe_null_arg,
             const LEX_CSTRING *field_name_arg,
	     bool unsigned_arg)
    :Field_int((uchar*) 0, len_arg, maybe_null_arg ? (uchar*) "": 0,0,
               NONE, field_name_arg, 0, unsigned_arg)
    {}