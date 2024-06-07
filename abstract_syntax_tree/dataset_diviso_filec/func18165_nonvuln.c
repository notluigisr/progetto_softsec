virDomainHostdevRemove(virDomainDefPtr def, size_t i)
{
    virDomainHostdevDefPtr hostdev = def->hostdevs[i];

    VIR_DELETE_ELEMENT(def->hostdevs, i, def->nhostdevs);
    return hostdev;
}