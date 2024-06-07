date_s_xmlschema(int argc, VALUE *argv, VALUE klass)
{
    VALUE str, sg;

    rb_scan_args(argc, argv, "STR", &str, &sg);

    switch (argc) {
      case 0:
	str = rb_str_new2("STR");
      case 1:
	sg = INT2FIX(DEFAULT_SG);
    }

    {
	VALUE hash = date_s__xmlschema(klass, str);
	return d_new_by_frags(klass, hash, sg);
    }
}