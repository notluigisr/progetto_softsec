  void decode(bufferlist::iterator& bl) {
    __u8 struct_v;
    ::decode(struct_v, bl);
    ::decode(session_key, bl);
    ::decode(validity, bl);
  }