	for (int i = 0; i < pModConf->nOptions; ++i) {
		if (!valid_civetweb_option(valid_opts, pModConf->options[i].name)) {
			LogError(0, RS_RET_CONF_PARSE_WARNING, "STR"
			"STR");
			iRet = RS_RET_CONF_PARSE_WARNING;
		}
	}