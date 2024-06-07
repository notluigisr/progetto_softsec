sixel_allocator_calloc(
    sixel_allocator_t    *allocator,  
    size_t               nelm,        
    size_t               elsize)      
{
    
    assert(allocator);
    assert(allocator->fn_calloc);

    return allocator->fn_calloc(nelm, elsize);
}