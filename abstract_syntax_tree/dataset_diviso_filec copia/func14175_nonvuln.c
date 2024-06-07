virDomainMigratePerform3Params(virDomainPtr domain,
                               const char *dconnuri,
                               virTypedParameterPtr params,
                               int nparams,
                               const char *cookiein,
                               int cookieinlen,
                               char **cookieout,
                               int *cookieoutlen,
                               unsigned int flags)
{
    virConnectPtr conn;

    VIR_DOMAIN_DEBUG(domain, "STR"
                     "STR",
                     NULLSTR(dconnuri), params, nparams, cookiein,
                     cookieinlen, cookieout, cookieoutlen, flags);
    VIR_TYPED_PARAMS_DEBUG(params, nparams);

    virResetLastError();

    virCheckDomainReturn(domain, -1);
    conn = domain->conn;

    virCheckReadOnlyGoto(conn->flags, error);

    if (conn->driver->domainMigratePerform3Params) {
        int ret;
        ret = conn->driver->domainMigratePerform3Params(
                domain, dconnuri, params, nparams, cookiein, cookieinlen,
                cookieout, cookieoutlen, flags);
        if (ret < 0)
            goto error;
        return ret;
    }

    virReportUnsupportedError();

 error:
    virDispatchError(domain->conn);
    return -1;
}