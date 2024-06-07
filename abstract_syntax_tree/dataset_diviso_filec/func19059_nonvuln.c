handle_nsExtendOutput1Table(netsnmp_mib_handler          *handler,
                     netsnmp_handler_registration *reginfo,
                     netsnmp_agent_request_info   *reqinfo,
                     netsnmp_request_info         *requests)
{
    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_extend             *extension;
    int len;

    for ( request=requests; request; request=request->next ) {
        if (request->processed)
            continue;
        table_info = netsnmp_extract_table_info( request );
        extension  = (netsnmp_extend*)netsnmp_extract_table_row_data( request );

        DEBUGMSGTL(( "STR"));
        DEBUGMSGOID(("STR", request->requestvb->name,
                                              request->requestvb->name_length));
        DEBUGMSG((   "STR"));

        switch (reqinfo->mode) {
        case MODE_GET:
            if (!extension || !(extension->flags & NS_EXTEND_FLAGS_ACTIVE)) {
                
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHINSTANCE);
                continue;
            }
            if (!(extension->flags & NS_EXTEND_FLAGS_WRITEABLE) &&
                (netsnmp_cache_check_and_reload( extension->cache ) < 0 )) {
                
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHINSTANCE);
                continue;
            }
            if ((extension->flags & NS_EXTEND_FLAGS_WRITEABLE) &&
                (netsnmp_cache_check_expired( extension->cache ) == 1 )) {
                
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHINSTANCE);
                continue;
            }

            switch (table_info->colnum) {
            case COLUMN_EXTOUT1_OUTLEN:
                snmp_set_var_typed_value(
                     request->requestvb, ASN_INTEGER,
                    (u_char*)&extension->out_len, sizeof(int));
                break;
            case COLUMN_EXTOUT1_OUTPUT1:
                
                if (extension->numlines > 1) {
                    len = (extension->lines[1])-(extension->output) -1;
                } else if (extension->output) {
                    len = strlen(extension->output);
                } else {
                    len = 0;
                }
                snmp_set_var_typed_value(
                     request->requestvb, ASN_OCTET_STR,
                     extension->output, len);
                break;
            case COLUMN_EXTOUT1_OUTPUT2:
                snmp_set_var_typed_value(
                     request->requestvb, ASN_OCTET_STR,
                     extension->output,
                    (extension->output)?extension->out_len:0);
                break;
            case COLUMN_EXTOUT1_NUMLINES:
                snmp_set_var_typed_value(
                     request->requestvb, ASN_INTEGER,
                    (u_char*)&extension->numlines, sizeof(int));
                break;
            case COLUMN_EXTOUT1_RESULT:
                snmp_set_var_typed_value(
                     request->requestvb, ASN_INTEGER,
                    (u_char*)&extension->result, sizeof(int));
                break;
            default:
                netsnmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
                continue;
            }
            break;
        default:
            netsnmp_set_request_error(reqinfo, request, SNMP_ERR_GENERR);
            return SNMP_ERR_GENERR;
        }
    }
    return SNMP_ERR_NOERROR;
}