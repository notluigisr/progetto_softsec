int    nedpmallopt(nedpool *p, int parno, int value) THROWSPEC
{
	return mspace_mallopt(parno, value);
}