valid_db_path(const char *nominal)
{
    struct stat sb;
#if USE_HASHED_DB
    char suffix[] = DBM_SUFFIX;
    size_t need = strlen(nominal) + sizeof(suffix);
    char *result = malloc(need);

    if (result == 0)
	failed("STR");
    _nc_STRCPY(result, nominal, need);
    if (strcmp(result + need - sizeof(suffix), suffix)) {
	_nc_STRCAT(result, suffix, need);
    }
#else
    char *result = strdup(nominal);
#endif

    DEBUG(1, ("STR", result));
    if (stat(result, &sb) >= 0) {
#if USE_HASHED_DB
	if (!S_ISREG(sb.st_mode)
	    || access(result, R_OK | W_OK) != 0) {
	    DEBUG(1, ("STR"));
	    free(result);
	    result = 0;
	}
#else
	if (!S_ISDIR(sb.st_mode)
	    || access(result, R_OK | W_OK | X_OK) != 0) {
	    DEBUG(1, ("STR"));
	    free(result);
	    result = 0;
	}
#endif
    } else {
	
	unsigned leaf = _nc_pathlast(result);

	DEBUG(1, ("STR"));
	if (leaf) {
	    char save = result[leaf];
	    result[leaf] = 0;
	    if (stat(result, &sb) >= 0
		&& S_ISDIR(sb.st_mode)
		&& access(result, R_OK | W_OK | X_OK) == 0) {
		result[leaf] = save;
	    } else {
		DEBUG(1, ("STR", result));
		free(result);
		result = 0;
	    }
	} else {
	    DEBUG(1, ("STR"));
	    free(result);
	    result = 0;
	}
    }
    return result;
}