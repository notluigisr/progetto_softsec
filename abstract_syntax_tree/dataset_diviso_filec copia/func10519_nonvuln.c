static void serialize_plist(node_t* node, void* data)
{
    uint64_t *index_val = NULL;
    struct serialize_s *ser = (struct serialize_s *) data;
    uint64_t current_index = ser->objects->len;

    
    void* val = hash_table_lookup(ser->ref_table, node);
    if (val)
    {
        
        return;
    }
    
    index_val = (uint64_t *) malloc(sizeof(uint64_t));
    assert(index_val != NULL);
    *index_val = current_index;
    hash_table_insert(ser->ref_table, node, index_val);

    
    ptr_array_add(ser->objects, node);

    
    node_iterator_t *ni = node_iterator_create(node->children);
    node_t *ch;
    while ((ch = node_iterator_next(ni))) {
        serialize_plist(ch, data);
    }
    node_iterator_destroy(ni);

    return;
}