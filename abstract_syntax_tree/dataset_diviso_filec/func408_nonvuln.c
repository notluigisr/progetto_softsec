uscore_get()
{
    VALUE line;

    line = rb_lastline_get();
    if (TYPE(line) != T_STRING) {
	rb_raise(rb_eTypeError, "STR",
		 NIL_P(line) ? "STR" : rb_obj_classname(line));
    }
    return line;
}