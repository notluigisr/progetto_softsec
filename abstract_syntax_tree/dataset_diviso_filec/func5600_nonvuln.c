njs_generator_pop(njs_vm_t *vm, njs_generator_t *generator,
    njs_parser_node_t *node)
{
    return njs_generator_stack_pop(vm, generator, NULL);
}