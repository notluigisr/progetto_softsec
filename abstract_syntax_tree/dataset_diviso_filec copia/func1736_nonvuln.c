OPJ_BOOL opj_tcd_init_decode_tile (opj_tcd_t *p_tcd, OPJ_UINT32 p_tile_no)
{
	return opj_tcd_init_tile(p_tcd, p_tile_no, OPJ_FALSE, 0.5F, sizeof(opj_tcd_cblk_dec_t));
}