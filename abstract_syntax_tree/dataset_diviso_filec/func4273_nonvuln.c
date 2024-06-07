body(VALUE self) {
    agooReq	r = DATA_PTR(self);

    if (NULL == r) {
	rb_raise(rb_eArgError, "STR");
    }
    if (NULL == r->body.start) {
	return Qnil;
    }
    return rb_str_new(r->body.start, r->body.len);
}