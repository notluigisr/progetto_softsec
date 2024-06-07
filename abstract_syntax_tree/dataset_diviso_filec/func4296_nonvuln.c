rb_str_aset(str, indx, val)
    VALUE str;
    VALUE indx, val;
{
    long idx, beg;

    switch (TYPE(indx)) {
      case T_FIXNUM:
	idx = FIX2LONG(indx);
      num_index:
	if (RSTRING(str)->len <= idx) {
	  out_of_range:
	    rb_raise(rb_eIndexError, "STR", idx);
	}
	if (idx < 0) {
	    if (-idx > RSTRING(str)->len)
		goto out_of_range;
	    idx += RSTRING(str)->len;
	}
	if (FIXNUM_P(val)) {
	    rb_str_modify(str);
	    if (RSTRING(str)->len == idx) {
		RSTRING(str)->len += 1;
		RESIZE_CAPA(str, RSTRING(str)->len);
	    }
	    RSTRING(str)->ptr[idx] = FIX2INT(val) & 0xff;
	}
	else {
	    rb_str_splice(str, idx, 1, val);
	}
	return val;

      case T_REGEXP:
	rb_str_subpat_set(str, indx, 0, val);
	return val;

      case T_STRING:
	beg = rb_str_index(str, indx, 0);
	if (beg < 0) {
	    rb_raise(rb_eIndexError, "STR");
	}
	rb_str_splice(str, beg, RSTRING(indx)->len, val);
	return val;

      default:
	
	{
	    long beg, len;
	    if (rb_range_beg_len(indx, &beg, &len, RSTRING(str)->len, 2)) {
		rb_str_splice(str, beg, len, val);
		return val;
	    }
	}
	idx = NUM2LONG(indx);
	goto num_index;
    }
}