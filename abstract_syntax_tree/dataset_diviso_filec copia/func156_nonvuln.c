static int sqlite3_my_callback(void *pArg, int argc __attribute__((unused)),
			      char **argv,
			      char **columnNames __attribute__((unused)))
{
    char **result = (char**)pArg;

    if (argv == NULL) {
	*result = NULL;				
    } else if (argv[0] == NULL) {
	*result = strdup(SQL_NULL_VALUE);	
    } else {
	*result = strdup(argv[0]);
    }

    return 0;
}