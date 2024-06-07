int jpc_firstone(int x)
{
	int n;

	
	assert(x >= 0);

	n = -1;
	while (x > 0) {
		x >>= 1;
		++n;
	}
	return n;
}