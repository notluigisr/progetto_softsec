njs_generate_dest_index(njs_vm_t *vm, njs_generator_t *generator,
    njs_parser_node_t *node)
{
    njs_index_t         ret;
    njs_parser_node_t   *dest;
    njs_parser_scope_t  *scope;

    ret = njs_generate_children_indexes_release(vm, generator, node);
    if (njs_slow_path(ret != NJS_OK)) {
        return ret;
    }

    dest = node->dest;

    if (dest != NULL && dest->index != NJS_INDEX_NONE) {
        scope = njs_function_scope(node->scope);

        if (!scope->dest_disable) {
            return dest->index;
        }
    }

    return njs_generate_node_temp_index_get(vm, generator, node);
}