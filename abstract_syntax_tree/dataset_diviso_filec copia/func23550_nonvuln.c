njs_generate_for_update(njs_vm_t *vm, njs_generator_t *generator,
    njs_parser_node_t *node)
{
    njs_int_t                 ret;
    njs_parser_node_t         *condition, *update;
    njs_generator_loop_ctx_t  *ctx;

    ctx = generator->context;

    update = node->right->right->right;
    condition = node->right->left;

    ret = njs_generate_node_index_release(vm, generator, update);
    if (njs_slow_path(ret != NJS_OK)) {
        return ret;
    }

    

    if (condition != NULL) {
        njs_code_set_jump_offset(generator, njs_vmcode_jump_t,
                                 ctx->jump_offset);

        njs_generator_next(generator, njs_generate, condition);

        return njs_generator_after(vm, generator,
                                   njs_queue_first(&generator->stack), node,
                                   njs_generate_for_end, ctx, 0);
    }

    return njs_generate_for_end(vm, generator, node);
}