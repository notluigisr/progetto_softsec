static bool bin_raw_strings(RCore *r, int mode, int va) {
	RBinFile *bf = r_bin_cur (r->bin);
	bool new_bf = false;
	if (bf && strstr (bf->file, "STR")) {
		
		r_io_read_at (r->io, 0, bf->buf->buf, bf->size);
	}
	if (!r->file) {
		eprintf ("STR");
		return false;
	}
	if (!bf) {
		bf = R_NEW0 (RBinFile);
		if (!bf) {
			return false;
		}
		RIODesc *desc = r_io_desc_get (r->io, r->file->fd);
		if (!desc) {
			free (bf);
			return false;
		}
		bf->file = strdup (desc->name);
		bf->size = r_io_desc_size (desc);
		if (bf->size == UT64_MAX) {
			free (bf);
			return false;
		}
		bf->buf = r_buf_new_with_io (&r->bin->iob, r->file->fd);
#if 0
		bf->buf = r_buf_new ();
		if (!bf->buf) {
			free (bf);
			return false;
		}
		bf->buf->buf = malloc (bf->size);
		if (!bf->buf->buf) {
			free (bf->buf);
			free (bf);
			return false;
		}
		bf->buf->fd = r->file->fd;
		bf->buf->length = bf->size;
		r_io_read_at (r->io, 0, bf->buf->buf, bf->size);
#endif
		bf->o = NULL;
		bf->rbin = r->bin;
		new_bf = true;
		va = false;
	}
	RList *l = r_bin_raw_strings (bf, 0);
	_print_strings (r, l, mode, va);
	if (new_bf) {
		r_buf_free (bf->buf);
		bf->buf = NULL;
		bf->id = -1;
		r_bin_file_free (bf);
	}
	return true;
}