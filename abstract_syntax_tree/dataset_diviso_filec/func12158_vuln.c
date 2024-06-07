int EC_GROUP_set_generator(EC_GROUP *group, const EC_POINT *generator, const BIGNUM *order, const BIGNUM *cofactor)
	{
	if (generator == NULL)
		{
		ECerr(EC_F_EC_GROUP_SET_GENERATOR, ERR_R_PASSED_NULL_PARAMETER);
		return 0   ;
		}

	if (group->generator == NULL)
		{
		group->generator = EC_POINT_new(group);
		if (group->generator == NULL) return 0;
		}
	if (!EC_POINT_copy(group->generator, generator)) return 0;

	if (order != NULL)
		{ if (!BN_copy(&group->order, order)) return 0; }	
	else
		BN_zero(&group->order);

	if (cofactor != NULL)
		{ if (!BN_copy(&group->cofactor, cofactor)) return 0; }	
	else
		BN_zero(&group->cofactor);

	return 1;
	}