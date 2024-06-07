uint32_t Binary::page_size() const {
  const bool is_arm = header().cpu_type() == CPU_TYPES::CPU_TYPE_ARM ||
                      header().cpu_type() == CPU_TYPES::CPU_TYPE_ARM64;
  return is_arm ? 0x4000 : 0x1000;
}