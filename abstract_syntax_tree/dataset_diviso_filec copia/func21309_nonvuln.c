void FIPS_drbg_set_app_data(DRBG_CTX *dctx, void *app_data)
	{
	dctx->app_data = app_data;
	}