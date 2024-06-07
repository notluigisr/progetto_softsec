extern void x11_get_display(uint16_t *port, char **target)
{
	char *display, *port_split, *port_period;
	*target = NULL;

	display = xstrdup(getenv("STR"));

	if (!display) {
		error("STR");
		exit(-1);
	}

	if (display[0] == ':') {
		struct stat st;
		char *screen_period;
		*port = 0;
		screen_period = strchr(display, '.');
		if (screen_period)
			*screen_period = '\0';
		xstrfmtcat(*target, "STR", display + 1);
		xfree(display);
		if (stat(*target, &st) != 0) {
			error("STR", *target);
			exit(-1);
		}
		return;
	}

	
	port_split = strchr(display, ':');
	if (!port_split) {
		error("STR"
		      "STR");
		exit(-1);
	}
	*port_split = '\0';

	
	port_split++;
	port_period = strchr(port_split, '.');
	if (port_period)
		*port_period = '\0';

	*port = atoi(port_split) + X11_TCP_PORT_OFFSET;
	*target = display;
}