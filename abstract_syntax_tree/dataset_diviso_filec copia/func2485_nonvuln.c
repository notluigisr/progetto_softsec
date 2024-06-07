MOBI_RET mobi_xml_write_element_ns(xmlTextWriterPtr writer, const char *name, const char **content, const char *ns) {
    if (content) {
        size_t i = 0;
        while (i < OPF_META_MAX_TAGS) {
            if (content[i] == NULL) {
                break;
            }
            xmlChar *namespace = NULL;
            if (ns) {
                namespace = BAD_CAST ns;
            }
            int xml_ret = xmlTextWriterWriteElementNS(writer, namespace, BAD_CAST name, NULL, BAD_CAST content[i]);
            if (xml_ret < 0) {
                debug_print("STR", xml_ret, name, content[i]);
                return MOBI_XML_ERR;
            }
            i++;
        }
    }
    return MOBI_SUCCESS;
}