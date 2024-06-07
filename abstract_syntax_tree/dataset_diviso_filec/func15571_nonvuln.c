void errflush(const gs_memory_t *mem)
{
    if (!mem->gs_lib_ctx->core->stderr_fn)
        fflush(mem->gs_lib_ctx->core->fstderr);
    
}