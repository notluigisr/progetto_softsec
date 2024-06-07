int enc_untrusted_sched_getaffinity(pid_t pid, size_t cpusetsize,
                                    cpu_set_t *mask) {
  klinux_cpu_set_t klinux_mask{};
  int result = EnsureInitializedAndDispatchSyscall(
      asylo::system_call::kSYS_sched_getaffinity, pid,
      static_cast<uint64_t>(cpusetsize), &klinux_mask);
  
  
  
  if (result < 0) {
    return -1;
  }
  if (!FromkLinuxCpuSet(&klinux_mask, mask)) {
    errno = EFAULT;
    return -1;
  }
  return 0;
}