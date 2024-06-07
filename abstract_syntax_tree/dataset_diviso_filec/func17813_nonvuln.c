static pj_status_t avi_on_destroy(pjmedia_port *this_port)
{
    struct avi_reader_port *fport = (struct avi_reader_port*) this_port;

    pj_assert(this_port->info.signature == SIGNATURE);

    if (fport->subscribed) {
    	pjmedia_event_unsubscribe(NULL, &file_on_event, fport, fport);
    	fport->subscribed = PJ_FALSE;
    }

    if (fport->fd != (pj_oshandle_t) (pj_ssize_t)-1)
        pj_file_close(fport->fd);
    return PJ_SUCCESS;
}