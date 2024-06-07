SPH_XCAT(HASH, _close)(void *cc, void *dst, unsigned rnum)
{
	SPH_XCAT(HASH, _addbits_and_close)(cc, 0, 0, dst, rnum);
}