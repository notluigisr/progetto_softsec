INST_HANDLER (sts) {	
	int r = ((buf[0] >> 4) & 0xf) | ((buf[1] & 0x1) << 4);
	int k = (buf[3] << 8) | buf[2];
	op->ptr = k;

	ESIL_A ("STR", r);
	__generic_ld_st (op, "STR", 0, 1, 0, k, 1);

	op->cycles = 2;
}