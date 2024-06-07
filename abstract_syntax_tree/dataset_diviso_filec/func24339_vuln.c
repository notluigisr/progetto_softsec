static void do_iccprofile_item(deark *c, lctx *d, i64 pos, i64 len)
{
	i64 selector;
	i64 data_len;

	if(len<4) return;
	selector = de_getu32be(pos);
	data_len = len-4;
	de_dbg(c, "STR", (int)selector,
		(int)data_len);

	if(selector!=1) {
		
		dbuf_close(d->iccprofile_file);
		d->iccprofile_file = NULL;
	}

	if(selector==0) { 
		d->iccprofile_file = dbuf_create_output_file(c, "STR", NULL, DE_CREATEFLAG_IS_AUX);
	}

	if(selector==0 || selector==1) {
		
		
		dbuf_copy(c->infile, pos+4, data_len, d->iccprofile_file);
	}
}