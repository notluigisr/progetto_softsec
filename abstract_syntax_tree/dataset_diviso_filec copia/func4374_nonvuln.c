void BN_consttime_swap(BN_ULONG condition, BIGNUM *a, BIGNUM *b, int nwords)
	{
	BN_ULONG t;
	int i;

	bn_wcheck_size(a, nwords);
	bn_wcheck_size(b, nwords);

	assert(a != b);
	assert((condition & (condition - 1)) == 0);
	assert(sizeof(BN_ULONG) >= sizeof(int));

	condition = ((condition - 1) >> (BN_BITS2 - 1)) - 1;

	t = (a->top^b->top) & condition;
	a->top ^= t;
	b->top ^= t;


	do { \
		t = (a->d[ind] ^ b->d[ind]) & condition; \
		a->d[ind] ^= t; \
		b->d[ind] ^= t; \
	} while (0)


	switch (nwords) {
	default:
		for (i = 10; i < nwords; i++) 
			BN_CONSTTIME_SWAP(i);
		
	case 10: BN_CONSTTIME_SWAP(9); 
	case 9: BN_CONSTTIME_SWAP(8); 
	case 8: BN_CONSTTIME_SWAP(7); 
	case 7: BN_CONSTTIME_SWAP(6); 
	case 6: BN_CONSTTIME_SWAP(5); 
	case 5: BN_CONSTTIME_SWAP(4); 
	case 4: BN_CONSTTIME_SWAP(3); 
	case 3: BN_CONSTTIME_SWAP(2); 
	case 2: BN_CONSTTIME_SWAP(1); 
	case 1: BN_CONSTTIME_SWAP(0);
	}
#undef BN_CONSTTIME_SWAP
}