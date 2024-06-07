inline SegmentReader::SegmentReader(Arena* arena, SegmentId id, kj::ArrayPtr<const word> ptr,
                                    ReadLimiter* readLimiter)
    : arena(arena), id(id), ptr(ptr), readLimiter(readLimiter) {}