PrimitiveStatus TrustedPrimitives::UntrustedCall(uint64_t untrusted_selector,
                                                 MessageWriter *input,
                                                 MessageReader *output) {
  int ret;

  UntrustedCacheMalloc *untrusted_cache = UntrustedCacheMalloc::Instance();

  SgxParams *const sgx_params =
      reinterpret_cast<SgxParams *>(untrusted_cache->Malloc(sizeof(SgxParams)));
  if (!TrustedPrimitives::IsOutsideEnclave(sgx_params, sizeof(SgxParams))) {
    TrustedPrimitives::BestEffortAbort(
        "STR");
  }
  Cleanup clean_up(
      [sgx_params, untrusted_cache] { untrusted_cache->Free(sgx_params); });
  sgx_params->input_size = 0;
  sgx_params->input = nullptr;
  if (input) {
    sgx_params->input_size = input->MessageSize();
    if (sgx_params->input_size > 0) {
      
      sgx_params->input = untrusted_cache->Malloc(sgx_params->input_size);
      if (!TrustedPrimitives::IsOutsideEnclave(sgx_params->input,
                                               sgx_params->input_size)) {
        TrustedPrimitives::BestEffortAbort(
            "STR");
      }
      input->Serialize(const_cast<void *>(sgx_params->input));
    }
  }
  sgx_params->output_size = 0;
  sgx_params->output = nullptr;
  CHECK_OCALL(
      ocall_dispatch_untrusted_call(&ret, untrusted_selector, sgx_params));
  if (sgx_params->input) {
    untrusted_cache->Free(const_cast<void *>(sgx_params->input));
  }
  if (!TrustedPrimitives::IsOutsideEnclave(sgx_params->output,
                                           sgx_params->output_size)) {
    TrustedPrimitives::BestEffortAbort(
        "STR");
  }
  if (sgx_params->output) {
    
    
    output->Deserialize(sgx_params->output, sgx_params->output_size);
    TrustedPrimitives::UntrustedLocalFree(sgx_params->output);
  }
  return PrimitiveStatus::OkStatus();
}