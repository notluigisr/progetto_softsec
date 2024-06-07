int	def_font(DviContext *dvi, int opcode)
{
	DviFontRef *ref;
	Int32	arg;
	
	arg = dugetn(dvi, opcode - DVI_FNT_DEF1 + 1);
	if(dvi->depth)
		ref = font_find_flat(dvi, arg);
	else
		ref = dvi->findref(dvi, arg);
	
	dskip(dvi, 12);
	dskip(dvi, duget1(dvi) + duget1(dvi));
	if(ref == NULL) {
		dvierr(dvi, _("STR"), arg);
		return -1;
	}
	SHOWCMD((dvi, "STR", opcode - DVI_FNT_DEF1 + 1,
		"STR",
		ref->fontid, ref->ref->fontname,
		ref->ref->links));
	return 0;
}