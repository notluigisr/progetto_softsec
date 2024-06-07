rb_str_sum(argc, argv, str)
    int argc;
    VALUE *argv;
    VALUE str;
{
    VALUE vbits;
    int bits;
    char *ptr, *p, *pend;
    long len;

    if (rb_scan_args(argc, argv, "STR", &vbits) == 0) {
	bits = 16;
    }
    else bits = NUM2INT(vbits);

    ptr = p = RSTRING(str)->ptr;
    len = RSTRING(str)->len;
    pend = p + len;
    if (bits >= sizeof(long)*CHAR_BIT) {
	VALUE sum = INT2FIX(0);

	while (p < pend) {
	    str_mod_check(str, ptr, len);
	    sum = rb_funcall(sum, '+', 1, INT2FIX((unsigned char)*p));
	    p++;
	}
	if (bits != 0) {
	    VALUE mod;

	    mod = rb_funcall(INT2FIX(1), rb_intern("STR"), 1, INT2FIX(bits));
	    mod = rb_funcall(mod, '-', 1, INT2FIX(1));
	    sum = rb_funcall(sum, '&', 1, mod);
	}
	return sum;
    }
    else {
       unsigned long sum = 0;

	while (p < pend) {
	    str_mod_check(str, ptr, len);
	    sum += (unsigned char)*p;
	    p++;
	}
	if (bits != 0) {
           sum &= (((unsigned long)1)<<bits)-1;
	}
	return rb_int2inum(sum);
    }
}