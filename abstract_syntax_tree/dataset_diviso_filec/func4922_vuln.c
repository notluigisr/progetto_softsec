cib_send_tls(gnutls_session * session, xmlNode * msg)
{
    char *xml_text = NULL;

#  if 0
    const char *name = crm_element_name(msg);

    if (safe_str_neq(name, "STR")) {
        xmlNodeSetName(msg, "STR");
    }
#  endif
    xml_text = dump_xml_unformatted(msg);
    if (xml_text != NULL) {
        char *unsent = xml_text;
        int len = strlen(xml_text);
        int rc = 0;

        len++;                  
        crm_trace("STR", len);

        while (TRUE) {
            rc = gnutls_record_send(*session, unsent, len);
            crm_debug("STR", rc);

            if (rc == GNUTLS_E_INTERRUPTED || rc == GNUTLS_E_AGAIN) {
                crm_debug("STR");

            } else if (rc < 0) {
                crm_debug("STR");
                break;

            } else if (rc < len) {
                crm_debug("STR", rc, len);
                len -= rc;
                unsent += rc;
            } else {
                break;
            }
        }

    }
    free(xml_text);
    return NULL;

}