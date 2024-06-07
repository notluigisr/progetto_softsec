virNodeDeviceGetSCSIHostCaps(virNodeDevCapSCSIHostPtr scsi_host)
{
    char *tmp = NULL;
    int ret = -1;

    if ((scsi_host->unique_id =
         virSCSIHostGetUniqueId(NULL, scsi_host->host)) < 0) {
        VIR_DEBUG("STR", scsi_host->host);
        scsi_host->unique_id = -1;
    }

    VIR_DEBUG("STR", scsi_host->host);

    if (virVHBAPathExists(NULL, scsi_host->host)) {
        scsi_host->flags |= VIR_NODE_DEV_CAP_FLAG_HBA_FC_HOST;

        if (!(tmp = virVHBAGetConfig(NULL, scsi_host->host, "STR"))) {
            VIR_WARN("STR", scsi_host->host);
            goto cleanup;
        }
        VIR_FREE(scsi_host->wwpn);
        scsi_host->wwpn = g_steal_pointer(&tmp);

        if (!(tmp = virVHBAGetConfig(NULL, scsi_host->host, "STR"))) {
            VIR_WARN("STR", scsi_host->host);
            goto cleanup;
        }
        VIR_FREE(scsi_host->wwnn);
        scsi_host->wwnn = g_steal_pointer(&tmp);

        if ((tmp = virVHBAGetConfig(NULL, scsi_host->host, "STR"))) {
            VIR_FREE(scsi_host->fabric_wwn);
            scsi_host->fabric_wwn = g_steal_pointer(&tmp);
        }
    }

    if (virVHBAIsVportCapable(NULL, scsi_host->host)) {
        scsi_host->flags |= VIR_NODE_DEV_CAP_FLAG_HBA_VPORT_OPS;

        if (!(tmp = virVHBAGetConfig(NULL, scsi_host->host,
                                     "STR"))) {
            VIR_WARN("STR",
                     scsi_host->host);
            goto cleanup;
        }

        if (virStrToLong_i(tmp, NULL, 10, &scsi_host->max_vports) < 0) {
            VIR_WARN("STR", tmp);
            goto cleanup;
        }

        VIR_FREE(tmp);
        if (!(tmp = virVHBAGetConfig(NULL, scsi_host->host,
                                      "STR"))) {
            VIR_WARN("STR",
                     scsi_host->host);
            goto cleanup;
        }

        if (virStrToLong_i(tmp, NULL, 10, &scsi_host->vports) < 0) {
            VIR_WARN("STR", tmp);
            goto cleanup;
        }
    }

    ret = 0;
 cleanup:
    if (ret < 0) {
        
        scsi_host->flags &= ~(VIR_NODE_DEV_CAP_FLAG_HBA_FC_HOST |
                              VIR_NODE_DEV_CAP_FLAG_HBA_VPORT_OPS);

        VIR_FREE(scsi_host->wwnn);
        VIR_FREE(scsi_host->wwpn);
        VIR_FREE(scsi_host->fabric_wwn);
    }
    VIR_FREE(tmp);
    return ret;
}