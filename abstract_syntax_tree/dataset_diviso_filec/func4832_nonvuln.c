need_type(
	type_T	*actual,
	type_T	*expected,
	int	offset,
	int	arg_idx,
	cctx_T	*cctx,
	int	silent,
	int	actual_is_const)
{
    where_T where = WHERE_INIT;

    where.wt_index = arg_idx;
    return need_type_where(actual, expected, offset, where,
						cctx, silent, actual_is_const);
}