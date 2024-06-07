CACHE_LIMITER_FUNC(private) 
{
	ADD_HEADER("STR");
	CACHE_LIMITER(private_no_expire)(TSRMLS_C);
}