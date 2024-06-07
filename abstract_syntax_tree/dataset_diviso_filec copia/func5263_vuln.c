bool do_find_state(ctx_t &ctx)
{
    kernels_t &kernels = ctx.dc_kernels;
    const closure_t &closure = ctx.state;

    
    if (closure.size() == 0) {
        ctx.dc_target = dfa_t::NIL;
        ctx.dc_actions = NULL;
        return false;
    }

    
    reserve_buffers<ctx_t, stadfa>(ctx);
    kernel_t *k = ctx.dc_buffers.kernel;

    
    copy_to_buffer<stadfa>(closure, ctx.newprectbl, ctx.stadfa_actions, k);

    
    const uint32_t hash = hash_kernel(k);

    
    kernel_eq_t<ctx_t, stadfa> cmp_eq = {ctx};
    ctx.dc_target = kernels.find_with(hash, k, cmp_eq);
    if (ctx.dc_target != kernels_t::NIL) return false;

    
    
    if (!stadfa) {
        kernel_map_t<ctx_t, regless> cmp_map = {ctx};
        ctx.dc_target = kernels.find_with(hash, k, cmp_map);
        if (ctx.dc_target != kernels_t::NIL) return false;
    }

    
    kernel_t *kcopy = make_kernel_copy<stadfa>(k, ctx.dc_allocator);
    ctx.dc_target = kernels.push(hash, kcopy);
    return true;
}