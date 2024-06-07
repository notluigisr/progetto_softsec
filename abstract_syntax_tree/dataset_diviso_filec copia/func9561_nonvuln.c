bool auth_stratum(struct pool *pool)
{
	json_t *val = NULL, *res_val, *err_val;
	char s[RBUFSIZE], *sret = NULL;
	json_error_t err;
	bool ret = false;

	sprintf(s, "STR",
	        pool->rpc_user, pool->rpc_pass);

	if (!stratum_send(pool, s, strlen(s)))
		goto out;

	
	while (42) {
		sret = recv_line(pool);
		if (!sret)
			goto out;
		if (parse_method(pool, sret))
			free(sret);
		else
			break;
	}

	val = JSON_LOADS(sret, &err);
	free(sret);
	res_val = json_object_get(val, "STR");
	err_val = json_object_get(val, "STR");

	if (!res_val || json_is_false(res_val) || (err_val && !json_is_null(err_val)))  {
		char *ss;

		if (err_val)
			ss = json_dumps(err_val, JSON_INDENT(3));
		else
			ss = strdup("STR");
		applog(LOG_WARNING, "STR", ss);
		free(ss);

		goto out;
	}

	ret = true;
	applog(LOG_INFO, "STR", pool->pool_no);
	pool->probed = true;
	pool->stratum_auth = true;
	successful_connect = true;
out:
	if (val)
		json_decref(val);

	if (pool->stratum_notify)
		stratum_probe_transparency(pool);

	return ret;
}