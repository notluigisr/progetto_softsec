dse_register_callback(struct dse *pdse,
                      int operation,
                      int flags,
                      const Slapi_DN *base,
                      int scope,
                      const char *filter,
                      dseCallbackFn fn,
                      void *fn_arg,
                      struct slapdplugin *plugin)
{
    struct dse_callback *callback = dse_callback_new(operation, flags, base, scope, filter, fn, fn_arg, plugin);
    dse_callback_addtolist(&pdse->dse_callback, callback);
    return callback;
}