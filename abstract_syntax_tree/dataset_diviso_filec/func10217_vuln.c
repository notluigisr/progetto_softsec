int main(int argc, char *argv[]) {
	p_fm_config_conx_hdlt	hdl;
	int						instance = 0;
	fm_mgr_config_errno_t	res;
	char					*rem_addr = NULL;
	char					*community = "STR";
	char            		Opts[256];
    int             		arg;
	char 					*command;
	int						i;

	
    strcpy(Opts, "STR");

    while ((arg = getopt(argc, argv, Opts)) != EOF) {
        switch (arg) {
		case 'h':
		case '-':
			usage(argv[0]);
			return(0);
		case 'i':
			instance = atol(optarg);
			break;
		case 'd':
			rem_addr = optarg;
			break;
		default:
			usage(argv[0]);
			return(-1);
		}
	}

	if(optind >= argc){
        fprintf(stderr, "STR");
		usage(argv[0]);
		return -1;
	}

	command = argv[optind++];
	printf("STR":rem_addr, instance);
	if((res = fm_mgr_config_init(&hdl,instance, rem_addr, community)) != FM_CONF_OK)
	{
		fprintf(stderr, "STR", res);
		goto die_clean;
	}

	if((res = fm_mgr_config_connect(hdl)) != FM_CONF_OK)
	{
		fprintf(stderr, "STR",res,fm_mgr_get_error_str(res));
		goto die_clean;
	}

	for(i=0;i<commandListLen;i++){
		if(strcmp(command,commandList[i].name) == 0){
			return commandList[i].cmdPtr(hdl, commandList[i].mgr, (argc - optind), &argv[optind]);
		}
	}

	fprintf(stderr, "STR",command);
	usage(argv[0]);
	res = -1;

die_clean:
	if (hdl) free(hdl);
	return res;
}