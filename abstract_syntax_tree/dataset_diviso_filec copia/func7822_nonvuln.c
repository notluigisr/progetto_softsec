njs_generate_if_statement_then(njs_vm_t *vm, njs_generator_t *generator,
    njs_parser_node_t *node)
{
    njs_int_t          ret;
    njs_jump_off_t     *jump_offset, label_offset;
    njs_vmcode_jump_t  *jump;

    ret = njs_generate_node_index_release(vm, generator, node->left);
    if (njs_slow_path(ret != NJS_OK)) {
        return ret;
    }

    jump_offset = (njs_jump_off_t *) generator->context;
    label_offset = *jump_offset + offsetof(njs_vmcode_cond_jump_t, offset);

    njs_generate_code_jump(generator, jump, 0);
    njs_code_set_offset(generator, label_offset, *jump_offset);

    *jump_offset = njs_code_offset(generator, jump);

    njs_generator_next(generator, njs_generate, node->right);

    return njs_generator_after(vm, generator,
                               njs_queue_first(&generator->stack), node,
                               njs_generate_if_statement_else,
                               jump_offset, 0);
}