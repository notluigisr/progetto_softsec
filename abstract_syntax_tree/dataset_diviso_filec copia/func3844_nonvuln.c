Word getResponseBodyBufferBytesHandler(void* raw_context, Word start, Word length, Word ptr_ptr,
                                       Word size_ptr) {
  auto context = WASM_CONTEXT(raw_context);
  auto result = context->getResponseBodyBufferBytes(start.u64_, length.u64_);
  context->wasm()->copyToPointerSize(result, ptr_ptr.u64_, size_ptr.u64_);
  return wasmResultToWord(WasmResult::Ok);
}