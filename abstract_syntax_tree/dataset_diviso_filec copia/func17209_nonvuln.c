lys_implemented_module(const struct lys_module *mod)
{
    FUN_IN;

    struct ly_ctx *ctx;
    int i;

    if (!mod || mod->implemented) {
        
        return (struct lys_module *)mod;
    }

    ctx = mod->ctx;
    for (i = 0; i < ctx->models.used; i++) {
        if (!ctx->models.list[i]->implemented) {
            continue;
        }

        if (ly_strequal(mod->name, ctx->models.list[i]->name, 1)) {
            
            return ctx->models.list[i];
        }
    }

    
    return (struct lys_module *)mod;
}