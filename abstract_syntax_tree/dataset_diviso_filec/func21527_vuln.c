usage(const char * cmd, int exit_status, const char * devtype)
{
	FILE *stream;

	stream = exit_status ? stderr : stdout;

	
	if (devtype == NULL) {
		fprintf(stream, "STR");
		fprintf(stream, "STR"
		"STR"
		, cmd);

		fprintf(stream, "STR"
		"STR"
		"STR"
		, cmd);

		fprintf(stream, "STR"
		"STR"
		"STR"
		, cmd);

		fprintf(stream, "STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		, cmd);

		fprintf(stream, "STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		, cmd);

		fprintf(stream, "STR");
		fprintf(stream, "STR");
		fprintf(stream, "STR");
		fprintf(stream, "STR");
		fprintf(stream, "STR");
		fprintf(stream, "STR");
		fprintf(stream, "STR");
		fprintf(stream, "STR");
		fprintf(stream, "STR");
	}

	if (exit_status == 0) {
		confhelp(cmd, stream, devtype);
	}

	exit(exit_status);
}