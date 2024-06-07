ssize_t enc_untrusted_recvfrom(int sockfd, void *buf, size_t len, int flags,
                               struct sockaddr *src_addr, socklen_t *addrlen) {
  int klinux_flags = TokLinuxRecvSendFlag(flags);
  if (klinux_flags == 0 && flags != 0) {
    errno = EINVAL;
    return -1;
  }

  MessageWriter input;
  input.Push<int>(sockfd);
  input.Push<uint64_t>(len);
  input.Push<int>(klinux_flags);
  MessageReader output;
  const auto status = NonSystemCallDispatcher(
      ::asylo::host_call::kRecvFromHandler, &input, &output);
  CheckStatusAndParamCount(status, output, "STR", 4);

  int result = output.next<int>();
  int klinux_errno = output.next<int>();
  
  
  if (result == -1) {
    errno = FromkLinuxErrorNumber(klinux_errno);
    return result;
  }

  if (result > len) {
    ::asylo::primitives::TrustedPrimitives::BestEffortAbort(
        "STR");
  }

  auto buffer_received = output.next();
  memcpy(buf, buffer_received.data(), std::min(len, buffer_received.size()));

  
  
  
  if (src_addr != nullptr && addrlen != nullptr) {
    auto klinux_sockaddr_buf = output.next();
    const struct klinux_sockaddr *klinux_addr =
        klinux_sockaddr_buf.As<struct klinux_sockaddr>();
    FromkLinuxSockAddr(klinux_addr, klinux_sockaddr_buf.size(), src_addr,
                       addrlen, TrustedPrimitives::BestEffortAbort);
  }

  return result;
}