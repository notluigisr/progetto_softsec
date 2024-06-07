rb_str_to_i(argc, argv, str)
    int argc;
    VALUE *argv;
    VALUE str;
{
    VALUE b;
    int base;

    rb_scan_args(argc, argv, "STR", &b);
    if (argc == 0) base = 10;
    else base = NUM2INT(b);

    if (base < 0) {
	rb_raise(rb_eArgError, "STR", base);
    }
    return rb_str_to_inum(str, base, Qfalse);
}