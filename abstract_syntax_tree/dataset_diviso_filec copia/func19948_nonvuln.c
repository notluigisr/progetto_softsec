Word grpcCancelHandler(void* raw_context, Word token) {
  auto context = WASM_CONTEXT(raw_context)->root_context();
  return wasmResultToWord(context->grpcCancel(token.u64_));
}