MaybeLocal<Object> AddIssuerChainToObject(
    X509Pointer* cert,
    Local<Object> object,
    StackOfX509&& peer_certs,
    Environment* const env) {
  Local<Context> context = env->isolate()->GetCurrentContext();
  cert->reset(sk_X509_delete(peer_certs.get(), 0));
  for (;;) {
    int i;
    for (i = 0; i < sk_X509_num(peer_certs.get()); i++) {
      X509* ca = sk_X509_value(peer_certs.get(), i);
      if (X509_check_issued(ca, cert->get()) != X509_V_OK)
        continue;

      Local<Object> ca_info;
      MaybeLocal<Object> maybe_ca_info = X509ToObject(env, ca);
      if (!maybe_ca_info.ToLocal(&ca_info))
        return MaybeLocal<Object>();

      if (!Set<Object>(context, object, env->issuercert_string(), ca_info))
        return MaybeLocal<Object>();
      object = ca_info;

      
      
      cert->reset(sk_X509_delete(peer_certs.get(), i));
      break;
    }

    
    if (i == sk_X509_num(peer_certs.get()))
      break;
  }
  return MaybeLocal<Object>(object);
}