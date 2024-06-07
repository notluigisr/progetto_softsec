sixel_allocator_realloc(
    sixel_allocator_t    *allocator,  
    void                 *p,          
    size_t               n)           
{
    
    assert(allocator);
    assert(allocator->fn_realloc);

    return allocator->fn_realloc(p, n);
}