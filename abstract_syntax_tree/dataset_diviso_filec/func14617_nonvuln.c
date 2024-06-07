  void ADDCALL sass_delete_data_context (struct Sass_Data_Context* ctx)
  {
    
    
    if (ctx->source_string) free(ctx->source_string);
    
    sass_clear_context(ctx); free(ctx);
  }