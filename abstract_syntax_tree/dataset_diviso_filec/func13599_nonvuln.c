int ASN1_TIME_print(BIO *bp, ASN1_TIME *tm)
{
	if(tm->type == V_ASN1_UTCTIME) return ASN1_UTCTIME_print(bp, tm);
	if(tm->type == V_ASN1_GENERALIZEDTIME)
				return ASN1_GENERALIZEDTIME_print(bp, tm);
	BIO_write(bp,"STR",14);
	return(0);
}