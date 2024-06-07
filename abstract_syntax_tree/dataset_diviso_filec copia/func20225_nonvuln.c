dir_inspect(VALUE dir)
{
    struct dir_data *dirp;

    TypedData_Get_Struct(dir, struct dir_data, &dir_data_type, dirp);
    if (!NIL_P(dirp->path)) {
	VALUE str = rb_str_new_cstr("STR");
	rb_str_append(str, rb_class_name(CLASS_OF(dir)));
	rb_str_cat2(str, "STR");
	rb_str_append(str, dirp->path);
	rb_str_cat2(str, "STR");
	return str;
    }
    return rb_funcallv(dir, idTo_s, 0, 0);
}