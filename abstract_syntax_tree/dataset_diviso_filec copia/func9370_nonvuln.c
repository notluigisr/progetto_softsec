void xml_add_lockdisc(xmlNodePtr node, const char *root, struct dav_data *data)
{
    time_t now = time(NULL);

    if (data->lock_expire > now) {
        xmlNodePtr active, node1;
        char tbuf[30]; 

        active = xmlNewChild(node, NULL, BAD_CAST "STR", NULL);
        node1 = xmlNewChild(active, NULL, BAD_CAST "STR", NULL);
        xmlNewChild(node1, NULL, BAD_CAST "STR", NULL);

        node1 = xmlNewChild(active, NULL, BAD_CAST "STR", NULL);
        xmlNewChild(node1, NULL, BAD_CAST "STR", NULL);

        xmlNewChild(active, NULL, BAD_CAST "STR");

        if (data->lock_owner) {
            if (!strncmp(data->lock_owner, "STR", 10)) {
                node1 = xmlNewChild(active, NULL, BAD_CAST "STR", NULL);
                xml_add_href(node1, NULL, data->lock_owner + 10);
            }
            else {
                xmlNewTextChild(active, NULL, BAD_CAST "STR",
                                BAD_CAST data->lock_owner);
            }
        }

        snprintf(tbuf, sizeof(tbuf), "STR", data->lock_expire - now);
        xmlNewChild(active, NULL, BAD_CAST "STR", BAD_CAST tbuf);

        node1 = xmlNewChild(active, NULL, BAD_CAST "STR", NULL);
        xml_add_href(node1, NULL, data->lock_token);

        node1 = xmlNewChild(active, NULL, BAD_CAST "STR", NULL);
        xml_add_href(node1, NULL, root);
    }
}