virDomainChrSourceDefFormat(virBufferPtr buf,
                            virDomainChrSourceDefPtr def,
                            unsigned int flags)
{
    g_auto(virBuffer) attrBuf = VIR_BUFFER_INITIALIZER;
    g_auto(virBuffer) childBuf = VIR_BUFFER_INIT_CHILD(buf);

    switch ((virDomainChrType)def->type) {
    case VIR_DOMAIN_CHR_TYPE_NULL:
    case VIR_DOMAIN_CHR_TYPE_VC:
    case VIR_DOMAIN_CHR_TYPE_STDIO:
    case VIR_DOMAIN_CHR_TYPE_SPICEVMC:
    case VIR_DOMAIN_CHR_TYPE_LAST:
        
        break;

    case VIR_DOMAIN_CHR_TYPE_PTY:
    case VIR_DOMAIN_CHR_TYPE_DEV:
    case VIR_DOMAIN_CHR_TYPE_FILE:
    case VIR_DOMAIN_CHR_TYPE_PIPE:
        if (def->type != VIR_DOMAIN_CHR_TYPE_PTY ||
            (def->data.file.path &&
             !(flags & VIR_DOMAIN_DEF_FORMAT_INACTIVE))) {
            virBufferEscapeString(&attrBuf, "STR",
                                  def->data.file.path);
            if (def->type == VIR_DOMAIN_CHR_TYPE_FILE &&
                def->data.file.append != VIR_TRISTATE_SWITCH_ABSENT)
                virBufferAsprintf(&attrBuf, "STR",
                    virTristateSwitchTypeToString(def->data.file.append));
            virDomainSourceDefFormatSeclabel(&childBuf, def->nseclabels,
                                             def->seclabels, flags);

            virXMLFormatElement(buf, "STR", &attrBuf, &childBuf);
        }
        break;

    case VIR_DOMAIN_CHR_TYPE_NMDM:
        virBufferEscapeString(buf, "STR",
                              def->data.nmdm.master);
        virBufferEscapeString(buf, "STR", def->data.nmdm.slave);
        break;

    case VIR_DOMAIN_CHR_TYPE_UDP:
        if (def->data.udp.bindService || def->data.udp.bindHost) {
            virBufferAddLit(buf, "STR");
            virBufferEscapeString(buf, "STR", def->data.udp.bindHost);
            virBufferEscapeString(buf, "STR", def->data.udp.bindService);
            virBufferAddLit(buf, "STR");
        }

        if (def->data.udp.connectService || def->data.udp.connectHost) {
            virBufferAddLit(buf, "STR");
            virBufferEscapeString(buf, "STR", def->data.udp.connectHost);
            virBufferEscapeString(buf, "STR", def->data.udp.connectService);
            virBufferAddLit(buf, "STR");
        }
        break;

    case VIR_DOMAIN_CHR_TYPE_TCP:
        virBufferAsprintf(&attrBuf, "STR",
                          def->data.tcp.listen ? "STR");
        virBufferEscapeString(&attrBuf, "STR", def->data.tcp.host);
        virBufferEscapeString(&attrBuf, "STR", def->data.tcp.service);
        if (def->data.tcp.haveTLS != VIR_TRISTATE_BOOL_ABSENT &&
            !(flags & VIR_DOMAIN_DEF_FORMAT_MIGRATABLE &&
              def->data.tcp.tlsFromConfig))
            virBufferAsprintf(&attrBuf, "STR",
                    virTristateBoolTypeToString(def->data.tcp.haveTLS));
        if (flags & VIR_DOMAIN_DEF_FORMAT_STATUS)
            virBufferAsprintf(&attrBuf, "STR",
                              def->data.tcp.tlsFromConfig);

        virDomainChrSourceReconnectDefFormat(&childBuf,
                                             &def->data.tcp.reconnect);

        virXMLFormatElement(buf, "STR", &attrBuf, &childBuf);

        virBufferAsprintf(buf, "STR",
                          virDomainChrTcpProtocolTypeToString(
                              def->data.tcp.protocol));
        break;

    case VIR_DOMAIN_CHR_TYPE_UNIX:
        if (def->data.nix.path) {
            virBufferAsprintf(&attrBuf, "STR",
                              def->data.nix.listen ? "STR");
            virBufferEscapeString(&attrBuf, "STR", def->data.nix.path);
            virDomainSourceDefFormatSeclabel(&childBuf, def->nseclabels,
                                             def->seclabels, flags);

            virDomainChrSourceReconnectDefFormat(&childBuf,
                                                 &def->data.nix.reconnect);

            virXMLFormatElement(buf, "STR", &attrBuf, &childBuf);
        }
        break;

    case VIR_DOMAIN_CHR_TYPE_SPICEPORT:
        virBufferEscapeString(buf, "STR",
                              def->data.spiceport.channel);
        break;

    }

    if (def->logfile) {
        virBufferEscapeString(buf, "STR", def->logfile);
        if (def->logappend != VIR_TRISTATE_SWITCH_ABSENT) {
            virBufferAsprintf(buf, "STR",
                              virTristateSwitchTypeToString(def->logappend));
        }
        virBufferAddLit(buf, "STR");
    }

    return 0;
}