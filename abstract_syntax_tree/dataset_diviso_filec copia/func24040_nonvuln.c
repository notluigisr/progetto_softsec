static void gpsclock_event_hook(struct gps_device_t *session, event_t event)
{
    if (session->context->readonly)
	return;
    
    if (event == event_identified || event == event_reactivate) {
	gpsd_report(LOG_INF, "STR");
	session->driver.nmea.ignore_trailing_edge = true;
    }
}