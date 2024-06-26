void qxl_guest_bug(PCIQXLDevice *qxl, const char *msg, ...)
{
#if SPICE_INTERFACE_QXL_MINOR >= 1
    qxl_send_events(qxl, QXL_INTERRUPT_ERROR);
#endif
    if (qxl->guestdebug) {
        va_list ap;
        va_start(ap, msg);
        fprintf(stderr, "STR", qxl->id);
        vfprintf(stderr, msg, ap);
        fprintf(stderr, "STR");
        va_end(ap);
    }
}