xmlSchemaCheckParticleRangeOK(int rmin, int rmax,
			      int bmin, int bmax)
{
    if (rmin < bmin)
	return (1);
    if ((bmax != UNBOUNDED) &&
	(rmax > bmax))
	return (1);
    return (0);
}