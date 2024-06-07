virDomainHostdevDefValidate(const virDomainHostdevDef *hostdev)
{
    if (hostdev->mode == VIR_DOMAIN_HOSTDEV_MODE_SUBSYS) {
        switch ((virDomainHostdevSubsysType) hostdev->source.subsys.type) {
        case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_PCI:
            if (hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_NONE &&
                hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_UNASSIGNED &&
                hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_PCI) {
                virReportError(VIR_ERR_INTERNAL_ERROR, "STR",
                               _("STR"
                                 "STR"));
                return -1;
            }
            break;
        case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_SCSI:
            if (hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_NONE &&
                hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_DRIVE) {
                virReportError(VIR_ERR_XML_ERROR, "STR",
                               _("STR"
                                 "STR"));
                return -1;
            }
            break;
        case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_SCSI_HOST:
            if (hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_NONE &&
                hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_PCI &&
                hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_CCW) {
                virReportError(VIR_ERR_XML_ERROR, "STR",
                               _("STR"
                                 "STR"));
                return -1;
            }
            break;
        case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_USB:
            if (hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_NONE &&
                hostdev->info->type != VIR_DOMAIN_DEVICE_ADDRESS_TYPE_USB) {
                virReportError(VIR_ERR_XML_ERROR, "STR",
                               _("STR"));
                return -1;
            }
            break;
        case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_MDEV:
        case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_LAST:
            break;
        }
    }
    return 0;
}