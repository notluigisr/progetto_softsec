PJ_DEF(pj_status_t) pj_ssl_cert_load_from_files2(pj_pool_t *pool,
						 const pj_str_t *CA_file,
						 const pj_str_t *CA_path,
						 const pj_str_t *cert_file,
						 const pj_str_t *privkey_file,
						 const pj_str_t *privkey_pass,
						 pj_ssl_cert_t **p_cert)
{
    pj_ssl_cert_t *cert;

    PJ_ASSERT_RETURN(pool && (CA_file || CA_path) && cert_file &&
		     privkey_file,
		     PJ_EINVAL);

    cert = PJ_POOL_ZALLOC_T(pool, pj_ssl_cert_t);
    if (CA_file) {
    	pj_strdup_with_null(pool, &cert->CA_file, CA_file);
    }
    if (CA_path) {
    	pj_strdup_with_null(pool, &cert->CA_path, CA_path);
    }
    pj_strdup_with_null(pool, &cert->cert_file, cert_file);
    pj_strdup_with_null(pool, &cert->privkey_file, privkey_file);
    pj_strdup_with_null(pool, &cert->privkey_pass, privkey_pass);

    *p_cert = cert;

    return PJ_SUCCESS;
}