IOBuf IOBuf::cloneCoalescedAsValueWithHeadroomTailroom(
    std::size_t newHeadroom, std::size_t newTailroom) const {
  if (!isChained() && newHeadroom <= headroom() && newTailroom <= tailroom()) {
    return cloneOneAsValue();
  }
  
  const std::size_t newLength = computeChainDataLength();
  const std::size_t newCapacity = newLength + newHeadroom + newTailroom;
  IOBuf newBuf{CREATE, newCapacity};
  newBuf.advance(newHeadroom);

  auto current = this;
  do {
    if (current->length() > 0) {
      DCHECK_NOTNULL(current->data());
      DCHECK_LE(current->length(), newBuf.tailroom());
      memcpy(newBuf.writableTail(), current->data(), current->length());
      newBuf.append(current->length());
    }
    current = current->next();
  } while (current != this);

  DCHECK_EQ(newLength, newBuf.length());
  DCHECK_EQ(newHeadroom, newBuf.headroom());
  DCHECK_LE(newTailroom, newBuf.tailroom());

  return newBuf;
}