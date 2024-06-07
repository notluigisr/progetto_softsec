void outflush(const gs_memory_t *mem)
{
    gs_lib_ctx_core_t *core = mem->gs_lib_ctx->core;
    if (core->stdout_is_redirected) {
        if (core->stdout_to_stderr) {
            if (!core->stderr_fn)
                fflush(core->fstderr);
        }
        else
            gp_fflush(core->fstdout2);
    }
    else if (!core->stdout_fn)
        fflush(core->fstdout);
}