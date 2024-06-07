path_poly(PG_FUNCTION_ARGS)
{
	PATH	   *path = PG_GETARG_PATH_P(0);
	POLYGON    *poly;
	int			size;
	int			i;

	
	if (!path->closed)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("STR")));

	size = offsetof(POLYGON, p[0]) +sizeof(poly->p[0]) * path->npts;
	poly = (POLYGON *) palloc(size);

	SET_VARSIZE(poly, size);
	poly->npts = path->npts;

	for (i = 0; i < path->npts; i++)
	{
		poly->p[i].x = path->p[i].x;
		poly->p[i].y = path->p[i].y;
	}

	make_bound_box(poly);

	PG_RETURN_POLYGON_P(poly);
}