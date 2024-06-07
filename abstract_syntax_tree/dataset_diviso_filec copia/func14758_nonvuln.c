virDomainHostdevMatchSubsys(virDomainHostdevDefPtr a,
                            virDomainHostdevDefPtr b)
{
    if (a->source.subsys.type != b->source.subsys.type)
        return 0;

    switch ((virDomainHostdevSubsysType) a->source.subsys.type) {
    case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_PCI:
        return virDomainHostdevMatchSubsysPCI(a, b);
    case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_USB:
        return virDomainHostdevMatchSubsysUSB(a, b);
    case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_SCSI:
        if (a->source.subsys.u.scsi.protocol !=
            b->source.subsys.u.scsi.protocol)
            return 0;
        if (a->source.subsys.u.scsi.protocol ==
            VIR_DOMAIN_HOSTDEV_SCSI_PROTOCOL_TYPE_ISCSI)
            return virDomainHostdevMatchSubsysSCSIiSCSI(a, b);
        else
            return virDomainHostdevMatchSubsysSCSIHost(a, b);
    case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_SCSI_HOST:
        if (a->source.subsys.u.scsi_host.protocol !=
            b->source.subsys.u.scsi_host.protocol)
            return 0;
        if (STREQ(a->source.subsys.u.scsi_host.wwpn,
                  b->source.subsys.u.scsi_host.wwpn))
            return 1;
        else
            return 0;
    case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_MDEV:
        return virDomainHostdevMatchSubsysMediatedDev(a, b);
    case VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_LAST:
        return 0;
    }
    return 0;
}