Word getSharedDataHandler(void* raw_context, Word key_ptr, Word key_size, Word value_ptr_ptr,
                          Word value_size_ptr, Word cas_ptr) {
  auto context = WASM_CONTEXT(raw_context);
  auto key = context->wasmVm()->getMemory(key_ptr.u64_, key_size.u64_);
  if (!key) {
    return wasmResultToWord(WasmResult::InvalidMemoryAccess);
  }
  std::pair<std::string, uint32_t> data;
  WasmResult result = context->getSharedData(key.value(), &data);
  if (result != WasmResult::Ok) {
    return wasmResultToWord(result);
  }
  if (!context->wasm()->copyToPointerSize(data.first, value_ptr_ptr.u64_, value_size_ptr.u64_)) {
    return wasmResultToWord(WasmResult::InvalidMemoryAccess);
  }
  if (!context->wasmVm()->setMemory(cas_ptr.u64_, sizeof(uint32_t), &data.second)) {
    return wasmResultToWord(WasmResult::InvalidMemoryAccess);
  }
  return wasmResultToWord(WasmResult::Ok);
}