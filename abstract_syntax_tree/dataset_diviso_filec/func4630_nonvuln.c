void *enc_untrusted_realloc(void *ptr, size_t size) {
  MessageWriter input;
  input.Push(reinterpret_cast<uint64_t>(ptr));
  input.Push(static_cast<uint64_t>(size));

  MessageReader output;
  asylo::primitives::PrimitiveStatus status =
      asylo::host_call::NonSystemCallDispatcher(
          asylo::host_call::kReallocHandler, &input, &output);
  CheckStatusAndParamCount(status, output, "STR", 2);

  void *result = output.next<void *>();
  int klinux_errno = output.next<int>();

  
  
  if (!result && size != 0) {
    errno = FromkLinuxErrorNumber(klinux_errno);
  }

  if (!::asylo::primitives::TrustedPrimitives::IsOutsideEnclave(result, size)) {
    ::asylo::primitives::TrustedPrimitives::BestEffortAbort(
        "STR"
        "STR");
  }
  return result;
}