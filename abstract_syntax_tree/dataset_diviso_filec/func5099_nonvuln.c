virDomainHostdevMatch(virDomainHostdevDefPtr a,
                      virDomainHostdevDefPtr b)
{
    if (a->mode != b->mode)
        return 0;

    switch (a->mode) {
    case VIR_DOMAIN_HOSTDEV_MODE_SUBSYS:
        return virDomainHostdevMatchSubsys(a, b);
    case VIR_DOMAIN_HOSTDEV_MODE_CAPABILITIES:
        return virDomainHostdevMatchCaps(a, b);
    }
    return 0;
}