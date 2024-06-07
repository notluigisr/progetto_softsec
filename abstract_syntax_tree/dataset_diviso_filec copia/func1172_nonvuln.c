virDomainResourceDefFree(virDomainResourceDefPtr resource)
{
    if (!resource)
        return;

    VIR_FREE(resource->partition);
    VIR_FREE(resource);
}