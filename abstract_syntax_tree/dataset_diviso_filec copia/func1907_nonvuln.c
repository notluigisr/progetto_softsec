static int rec_cmp(const struct dnsp_DnssrvRpcRecord *r1,
		   const struct dnsp_DnssrvRpcRecord *r2)
{
	if (r1->wType != r2->wType) {
		
		return r2->wType - r1->wType;
	}
	
	return r1->dwTimeStamp - r2->dwTimeStamp;
}