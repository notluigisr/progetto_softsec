libxlDomainDestroyInternal(libxlDriverPrivate *driver,
                           virDomainObj *vm)
{
    g_autoptr(libxlDriverConfig) cfg = libxlDriverConfigGet(driver);
    libxlDomainObjPrivate *priv = vm->privateData;
    int ret = -1;

    
    priv->ignoreDeathEvent = true;
    
    virObjectUnlock(vm);
    ret = libxl_domain_destroy(cfg->ctx, vm->def->id, NULL);
    virObjectLock(vm);
    if (ret)
        priv->ignoreDeathEvent = false;

    return ret;
}