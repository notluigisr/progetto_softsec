cib_send_plaintext(int sock, xmlNode * msg)
{
    char *xml_text = dump_xml_unformatted(msg);

    if (xml_text != NULL) {
        int rc = 0;
        char *unsent = xml_text;
        int len = strlen(xml_text);

        len++;                  
        crm_trace("STR", sock, len);
  retry:
        rc = write(sock, unsent, len);
        if (rc < 0) {
            switch (errno) {
                case EINTR:
                case EAGAIN:
                    crm_trace("STR");
                    goto retry;
                default:
                    crm_perror(LOG_ERR, "STR", rc, len);
                    break;
            }

        } else if (rc < len) {
            crm_trace("STR", rc, len);
            len -= rc;
            unsent += rc;
            goto retry;

        } else {
            crm_trace("STR", rc, xml_text);
        }
    }
    free(xml_text);
    return NULL;

}