void fmtutil_macbitmap_read_pixmap_only_fields(deark *c, dbuf *f, struct fmtutil_macbitmap_info *bi,
	i64 pos)
{
	i64 pixmap_version;
	i64 pack_size;
	i64 plane_bytes;
	i64 n;

	de_dbg(c, "STR", (int)pos);
	de_dbg_indent(c, 1);

	pixmap_version = dbuf_getu16be(f, pos+0);
	de_dbg(c, "STR", (int)pixmap_version);

	bi->packing_type = dbuf_getu16be(f, pos+2);
	de_dbg(c, "STR", (int)bi->packing_type);

	pack_size = dbuf_getu32be(f, pos+4);
	de_dbg(c, "STR", (int)pack_size);

	bi->hdpi = pict_read_fixed(f, pos+8);
	bi->vdpi = pict_read_fixed(f, pos+12);
	de_dbg(c, "STR", bi->hdpi, bi->vdpi);

	bi->pixeltype = dbuf_getu16be(f, pos+16);
	bi->pixelsize = dbuf_getu16be(f, pos+18);
	bi->cmpcount = dbuf_getu16be(f, pos+20);
	bi->cmpsize = dbuf_getu16be(f, pos+22);
	de_dbg(c, "STR",
		(int)bi->pixeltype, (int)bi->pixelsize, (int)bi->cmpcount, (int)bi->cmpsize);

	bi->pdwidth = (bi->rowbytes*8)/bi->pixelsize;
	if(bi->pdwidth < bi->npwidth) {
		bi->pdwidth = bi->npwidth;
	}

	plane_bytes = dbuf_getu32be(f, pos+24);
	de_dbg(c, "STR", (int)plane_bytes);

	bi->pmTable = (u32)dbuf_getu32be(f, pos+28);
	de_dbg(c, "STR", (unsigned int)bi->pmTable);

	n = dbuf_getu32be(f, pos+32);
	de_dbg(c, "STR", (unsigned int)n);

	de_dbg_indent(c, -1);
}