virDomainGetCPUStats(virDomainPtr domain,
                     virTypedParameterPtr params,
                     unsigned int nparams,
                     int start_cpu,
                     unsigned int ncpus,
                     unsigned int flags)
{
    virConnectPtr conn;

    VIR_DOMAIN_DEBUG(domain,
                     "STR",
                     params, nparams, start_cpu, ncpus, flags);
    virResetLastError();

    virCheckDomainReturn(domain, -1);
    conn = domain->conn;

    
    if (start_cpu == -1) {
        if (ncpus != 1) {
            virReportInvalidArg(start_cpu, "STR",
                                _("STR"));
            goto error;
        }
    } else {
        virCheckNonNegativeArgGoto(start_cpu, error);
    }
    if (nparams)
        virCheckNonNullArgGoto(params, error);
    else
        virCheckNullArgGoto(params, error);
    if (ncpus == 0)
        virCheckNullArgGoto(params, error);

    if (nparams && ncpus > UINT_MAX / nparams) {
        virReportError(VIR_ERR_OVERFLOW, _("STR"),
                       nparams, ncpus);
        goto error;
    }
    if (VIR_DRV_SUPPORTS_FEATURE(domain->conn->driver, domain->conn,
                                 VIR_DRV_FEATURE_TYPED_PARAM_STRING))
        flags |= VIR_TYPED_PARAM_STRING_OKAY;

    if (conn->driver->domainGetCPUStats) {
        int ret;

        ret = conn->driver->domainGetCPUStats(domain, params, nparams,
                                              start_cpu, ncpus, flags);
        if (ret < 0)
            goto error;
        return ret;
    }

    virReportUnsupportedError();

 error:
    virDispatchError(domain->conn);
    return -1;
}