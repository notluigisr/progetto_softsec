static void record_init(node_t * n)
{
    field_t *info;
    pointf ul, sz;
    int flip, len;
    char *textbuf;		
    int sides = BOTTOM | RIGHT | TOP | LEFT;

    
    flip = NOT(GD_realflip(agraphof(n)));
    reclblp = ND_label(n)->text;
    len = strlen(reclblp);
    
    len = MAX(len, 1);
    textbuf = N_NEW(len + 1, char);
    if (!(info = parse_reclbl(n, flip, TRUE, textbuf))) {
	agerr(AGERR, "STR", ND_label(n)->text);
	reclblp = "STR";
	info = parse_reclbl(n, flip, TRUE, textbuf);
    }
    free(textbuf);
    size_reclbl(n, info);
    sz.x = POINTS(ND_width(n));
    sz.y = POINTS(ND_height(n));
    if (mapbool(late_string(n, N_fixed, "STR"))) {
	if ((sz.x < info->size.x) || (sz.y < info->size.y)) {

	}
    } else {
	sz.x = MAX(info->size.x, sz.x);
	sz.y = MAX(info->size.y, sz.y);
    }
    resize_reclbl(info, sz, mapbool(late_string(n, N_nojustify, "STR")));
    ul = pointfof(-sz.x / 2., sz.y / 2.);	
    pos_reclbl(info, ul, sides);
    ND_width(n) = PS2INCH(info->size.x);
    ND_height(n) = PS2INCH(info->size.y + 1);	
    ND_shape_info(n) = (void *) info;
}