unique_ptr<IOBuf> IOBuf::cloneCoalesced() const {
  return std::make_unique<IOBuf>(cloneCoalescedAsValue());
}