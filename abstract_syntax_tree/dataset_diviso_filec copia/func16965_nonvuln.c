njs_generate_throw_statement(njs_vm_t *vm, njs_generator_t *generator,
    njs_parser_node_t *node)
{
    njs_generator_next(generator, njs_generate, node->right);

    return njs_generator_after(vm, generator,
                               njs_queue_first(&generator->stack), node,
                               njs_generate_throw_end, NULL, 0);
}