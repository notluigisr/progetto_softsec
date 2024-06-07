static void x509_end_cert(const br_x509_class **ctx)
{
  struct x509_context *x509 = (struct x509_context *)ctx;

  x509->minimal.vtable->end_cert(&x509->minimal.vtable);
}