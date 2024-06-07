virDomainManagedSaveRemove(virDomainPtr dom, unsigned int flags)
{
    virConnectPtr conn;

    VIR_DOMAIN_DEBUG(dom, "STR", flags);

    virResetLastError();

    virCheckDomainReturn(dom, -1);
    conn = dom->conn;

    virCheckReadOnlyGoto(conn->flags, error);

    if (conn->driver->domainManagedSaveRemove) {
        int ret;

        ret = conn->driver->domainManagedSaveRemove(dom, flags);
        if (ret < 0)
            goto error;
        return ret;
    }

    virReportUnsupportedError();

 error:
    virDispatchError(conn);
    return -1;
}