ff_push(ff_search_ctx_T *search_ctx, ff_stack_T *stack_ptr)
{
    
    
    if (stack_ptr != NULL)
    {
	stack_ptr->ffs_prev = search_ctx->ffsc_stack_ptr;
	search_ctx->ffsc_stack_ptr = stack_ptr;
    }
}