rb_str_check_dummy_enc(rb_encoding *enc)
{
    if (rb_enc_dummy_p(enc)) {
	rb_raise(rb_eEncCompatError, "STR",
		 rb_enc_name(enc));
    }
}