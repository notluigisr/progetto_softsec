static int bn2binpad(unsigned char *to, size_t tolen, BIGNUM *b)
	{
	size_t blen;
	blen = BN_num_bytes(b);
	
	if (blen > tolen)
		{
		BN_mask_bits(b, tolen << 3);
		
		blen = BN_num_bytes(b);
		}
	
	if (blen < tolen)
		{
		memset(to, 0, tolen - blen);
		to += tolen - blen;
		}

	
	BN_bn2bin(b, to);
	return 1;
	}