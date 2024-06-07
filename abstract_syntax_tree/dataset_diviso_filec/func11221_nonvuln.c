static int fsmSetFCaps(const char *path, const char *captxt)
{
    int rc = 0;
#if WITH_CAP
    if (captxt && *captxt != '\0') {
	cap_t fcaps = cap_from_text(captxt);
	if (fcaps == NULL || cap_set_file(path, fcaps) != 0) {
	    rc = RPMERR_SETCAP_FAILED;
	}
	if (_fsm_debug) {
	    rpmlog(RPMLOG_DEBUG, "STR", __func__,
		   path, captxt, (rc < 0 ? strerror(errno) : ""));
	}
	cap_free(fcaps);
    } 
#endif
    return rc;
}