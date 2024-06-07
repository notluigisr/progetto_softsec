void determinization(ctx_t &ctx)
{
    const uint32_t INITIAL_TAGS = init_tag_versions(ctx);

    
    const clos_t c0(ctx.nfa.root, 0, INITIAL_TAGS, HROOT, HROOT);
    ctx.reach.push_back(c0);
    tagged_epsilon_closure(ctx);
    find_state(ctx);

    
    
    
    for (uint32_t i = 0; i < ctx.dc_kernels.size(); ++i) {
        ctx.dc_origin = i;
        clear_caches(ctx);

        for (uint32_t c = 0; c < ctx.dfa.nchars; ++c) {
            reach_on_symbol(ctx, c);
            tagged_epsilon_closure(ctx);
            find_state(ctx);
        }
    }

    warn_nondeterministic_tags(ctx);
}