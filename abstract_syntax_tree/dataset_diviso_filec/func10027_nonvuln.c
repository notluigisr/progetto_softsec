rb_f_gsub(argc, argv)
    int argc;
    VALUE *argv;
{
    VALUE str = rb_str_dup(uscore_get());

    if (NIL_P(rb_str_gsub_bang(argc, argv, str)))
	return str;
    rb_lastline_set(str);
    return str;
}