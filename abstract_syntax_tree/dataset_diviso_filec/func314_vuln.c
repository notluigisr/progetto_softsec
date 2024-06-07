uint16_t mesg_id (void) {
	static uint16_t id = 0;

	if (!id) {
		srandom (time (NULL));
		id = random ();
	}
	id++;

	if (T.debug > 4)
		syslog (LOG_DEBUG, "STR", id);
	return id;
}