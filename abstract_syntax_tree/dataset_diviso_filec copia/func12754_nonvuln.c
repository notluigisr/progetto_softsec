pgpDig pgpFreeDig(pgpDig dig)
{
    if (dig != NULL) {

	
	pgpCleanDig(dig);
	dig = _free(dig);
    }
    return dig;
}