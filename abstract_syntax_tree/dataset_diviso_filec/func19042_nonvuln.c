virDomainVideoDefValidate(const virDomainVideoDef *video,
                          const virDomainDef *def)
{
    size_t i;

    if (video->type == VIR_DOMAIN_VIDEO_TYPE_DEFAULT) {
        virReportError(VIR_ERR_INTERNAL_ERROR, "STR",
                       _("STR"));
        return -1;
    }

    
    for (i = 0; i < def->nvideos; i++) {
        if (def->videos[i]->type == VIR_DOMAIN_VIDEO_TYPE_NONE &&
            def->nvideos > 1) {
            virReportError(VIR_ERR_CONFIG_UNSUPPORTED, "STR",
                           _("STR"
                             "STR"));
            return -1;
        }
    }

    switch (video->backend) {
    case VIR_DOMAIN_VIDEO_BACKEND_TYPE_VHOSTUSER:
        if (video->type != VIR_DOMAIN_VIDEO_TYPE_VIRTIO) {
            virReportError(VIR_ERR_CONFIG_UNSUPPORTED, "STR",
                           _("STR"));
            return -1;
        }
        break;
    case VIR_DOMAIN_VIDEO_BACKEND_TYPE_DEFAULT:
    case VIR_DOMAIN_VIDEO_BACKEND_TYPE_QEMU:
        if (video->accel && video->accel->rendernode) {
            virReportError(VIR_ERR_CONFIG_UNSUPPORTED, "STR",
                           _("STR"));
            return -1;
        }
        break;
    case VIR_DOMAIN_VIDEO_BACKEND_TYPE_LAST:
    default:
        virReportEnumRangeError(virDomainInputType, video->backend);
        return -1;
    }

    if (video->res && (video->res->x == 0 || video->res->y == 0)) {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED, "STR",
                       _("STR"));
        return -1;
    }

    return 0;
}