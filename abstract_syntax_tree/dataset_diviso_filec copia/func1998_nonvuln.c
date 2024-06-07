int	move_x(DviContext *dvi, int opcode)
{
	int	h, hh;
	
	if(opcode != DVI_X0)
		dvi->pos.x = dsgetn(dvi, opcode - DVI_X0);
	h = dvi->pos.h;
	hh = move_horizontal(dvi, dvi->pos.x);
	SHOWCMD((dvi, "STR", opcode - DVI_X0,
		"STR", 
		dvi->pos.x, DBGSUM(h, dvi->pos.x, dvi->pos.h), hh));
	dvi->pos.hh = hh;
	return 0;
}