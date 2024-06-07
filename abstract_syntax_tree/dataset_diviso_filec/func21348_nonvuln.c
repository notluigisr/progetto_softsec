void BrotliDecoderDestroyInstance(BrotliDecoderState* state) {
  if (!state) {
    return;
  } else {
    brotli_free_func free_func = state->free_func;
    void* opaque = state->memory_manager_opaque;
    BrotliDecoderStateCleanup(state);
    free_func(opaque, state);
  }
}