const char* WireFormat::_InternalParse(Message* msg, const char* ptr,
                                       internal::ParseContext* ctx) {
  const Descriptor* descriptor = msg->GetDescriptor();
  const Reflection* reflection = msg->GetReflection();
  GOOGLE_DCHECK(descriptor);
  GOOGLE_DCHECK(reflection);
  if (descriptor->options().message_set_wire_format()) {
    MessageSetParser message_set{msg, descriptor, reflection};
    return message_set.ParseMessageSet(ptr, ctx);
  }
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ReadTag(ptr, &tag);
    if (PROTOBUF_PREDICT_FALSE(ptr == nullptr)) return nullptr;
    if (tag == 0 || (tag & 7) == WireFormatLite::WIRETYPE_END_GROUP) {
      ctx->SetLastTag(tag);
      break;
    }
    const FieldDescriptor* field = nullptr;

    int field_number = WireFormatLite::GetTagFieldNumber(tag);
    field = descriptor->FindFieldByNumber(field_number);

    
    if (field == nullptr && descriptor->IsExtensionNumber(field_number)) {
      if (ctx->data().pool == nullptr) {
        field = reflection->FindKnownExtensionByNumber(field_number);
      } else {
        field =
            ctx->data().pool->FindExtensionByNumber(descriptor, field_number);
      }
    }

    ptr = _InternalParseAndMergeField(msg, ptr, ctx, tag, reflection, field);
    if (PROTOBUF_PREDICT_FALSE(ptr == nullptr)) return nullptr;
  }
  return ptr;
}