sraSpanRemove(sraSpan *span) {
  span->_prev->_next = span->_next;
  span->_next->_prev = span->_prev;
}