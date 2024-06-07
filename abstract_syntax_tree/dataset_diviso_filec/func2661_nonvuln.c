_equalLateralJoinInfo(const LateralJoinInfo *a, const LateralJoinInfo *b)
{
	COMPARE_BITMAPSET_FIELD(lateral_lhs);
	COMPARE_BITMAPSET_FIELD(lateral_rhs);

	return true;
}