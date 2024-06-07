static void ecprint(FILE *out, EC_GROUP *grp, EC_POINT *pt)
	{
	BIGNUM *x, *y;
	x = BN_new();
	y = BN_new();
	EC_POINT_get_affine_coordinates_GFp(grp, pt, x, y, NULL);
	bnprint(out, "STR", x);
	bnprint(out, "STR", y);
	BN_free(x);
	BN_free(y);
	}