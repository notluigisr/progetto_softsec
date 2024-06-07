MaybeLocal<Value> GetKeyUsage(Environment* env, X509* cert) {
  StackOfASN1 eku(static_cast<STACK_OF(ASN1_OBJECT)*>(
      X509_get_ext_d2i(cert, NID_ext_key_usage, nullptr, nullptr)));
  if (eku) {
    const int count = sk_ASN1_OBJECT_num(eku.get());
    MaybeStackBuffer<Local<Value>, 16> ext_key_usage(count);
    char buf[256];

    int j = 0;
    for (int i = 0; i < count; i++) {
      if (OBJ_obj2txt(buf,
                      sizeof(buf),
                      sk_ASN1_OBJECT_value(eku.get(), i), 1) >= 0) {
        ext_key_usage[j++] = OneByteString(env->isolate(), buf);
      }
    }

    return Array::New(env->isolate(), ext_key_usage.out(), count);
  }

  return Undefined(env->isolate());
}