ssize_t enc_untrusted_recvmsg(int sockfd, struct msghdr *msg, int flags) {
  size_t total_buffer_size = CalculateTotalMessageSize(msg);

  MessageWriter input;
  input.Push(sockfd);
  input.Push<uint64_t>(msg->msg_namelen);
  input.Push<uint64_t>(total_buffer_size);
  input.Push<uint64_t>(msg->msg_controllen);
  input.Push(msg->msg_flags);
  input.Push(flags);

  MessageReader output;

  const auto status = NonSystemCallDispatcher(
      ::asylo::host_call::kRecvMsgHandler, &input, &output);
  CheckStatusAndParamCount(status, output, "STR", 2,
                           false);

  ssize_t result = output.next<ssize_t>();
  int klinux_errno = output.next<int>();

  
  
  if (result == -1) {
    errno = FromkLinuxErrorNumber(klinux_errno);
    return result;
  }

  auto msg_name_extent = output.next();
  
  if (msg_name_extent.size() <= msg->msg_namelen) {
    msg->msg_namelen = msg_name_extent.size();
  }
  memcpy(msg->msg_name, msg_name_extent.As<char>(), msg->msg_namelen);

  
  
  auto msg_iov_extent = output.next();
  size_t total_bytes = msg_iov_extent.size();
  size_t bytes_copied = 0;
  for (int i = 0; i < msg->msg_iovlen && bytes_copied < total_bytes; ++i) {
    size_t bytes_to_copy =
        std::min(msg->msg_iov[i].iov_len, total_bytes - bytes_copied);
    memcpy(msg->msg_iov[i].iov_base, msg_iov_extent.As<char>() + bytes_copied,
           bytes_to_copy);
    bytes_copied += bytes_to_copy;
  }

  auto msg_control_extent = output.next();
  
  if (msg_control_extent.size() <= msg->msg_controllen) {
    msg->msg_controllen = msg_control_extent.size();
  }
  memcpy(msg->msg_control, msg_control_extent.As<char>(), msg->msg_controllen);

  return result;
}