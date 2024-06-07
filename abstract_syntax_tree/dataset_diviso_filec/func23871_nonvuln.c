bool Wasm::initialize(const std::string& code, bool allow_precompiled) {
  if (!wasm_vm_) {
    return false;
  }

  
  if (vm_id_.empty()) {
    vm_id_ = base64Sha256(code);
  }

  auto ok = wasm_vm_->load(code, allow_precompiled);
  if (!ok) {
    return false;
  }
  auto metadata = wasm_vm_->getCustomSection("STR");
  if (!metadata.empty()) {
    
    is_emscripten_ = true;
    auto start = reinterpret_cast<const uint8_t*>(metadata.data());
    auto end = reinterpret_cast<const uint8_t*>(metadata.data() + metadata.size());
    start = decodeVarint(start, end, &emscripten_metadata_major_version_);
    start = decodeVarint(start, end, &emscripten_metadata_minor_version_);
    start = decodeVarint(start, end, &emscripten_abi_major_version_);
    start = decodeVarint(start, end, &emscripten_abi_minor_version_);
    uint32_t temp;
    if (emscripten_metadata_major_version_ > 0 || emscripten_metadata_minor_version_ > 1) {
      
      start = decodeVarint(start, end, &temp);
    }
    start = decodeVarint(start, end, &temp);
    start = decodeVarint(start, end, &temp);
    if (emscripten_metadata_major_version_ > 0 || emscripten_metadata_minor_version_ > 0) {
      
      start = decodeVarint(start, end, &temp);
      start = decodeVarint(start, end, &temp);
      start = decodeVarint(start, end, &temp);
      decodeVarint(start, end, &temp);
      if (emscripten_metadata_major_version_ > 0 || emscripten_metadata_minor_version_ > 2) {
        
        start = decodeVarint(start, end, &emscripten_standalone_wasm_);
      }
    }
  }
  registerCallbacks();
  wasm_vm_->link(vm_id_);
  vm_context_ = std::make_shared<Context>(this);
  getFunctions();
  startVm(vm_context_.get());
  code_ = code;
  allow_precompiled_ = allow_precompiled;
  return true;
}