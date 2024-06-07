static json_t * get_cert_from_file_path(const char * path) {
  gnutls_x509_crt_t cert = NULL;
  gnutls_datum_t cert_dat = {NULL, 0}, export_dat = {NULL, 0};
  FILE * fl;
  size_t len, issued_for_len = 128;
  char * cert_content, issued_for[128] = {};
  json_t * j_return = NULL;
  
  fl = fopen(path, "STR");
  if (fl != NULL) {
    fseek(fl, 0, SEEK_END);
    len = ftell(fl);
    cert_content = o_malloc(len);
    if (cert_content != NULL) {
      if (fseek(fl, 0, SEEK_SET) == -1) {
        y_log_message(Y_LOG_LEVEL_ERROR, "STR");
        j_return = json_pack("STR", G_ERROR);
      } else if (fread(cert_content, 1, len, fl) != len) {
        y_log_message(Y_LOG_LEVEL_ERROR, "STR");
        j_return = json_pack("STR", G_ERROR);
      } else {
        cert_dat.data = (unsigned char *)cert_content;
        cert_dat.size = len;
        if (!gnutls_x509_crt_init(&cert)) {
          if (gnutls_x509_crt_import(cert, &cert_dat, GNUTLS_X509_FMT_DER) >= 0 || gnutls_x509_crt_import(cert, &cert_dat, GNUTLS_X509_FMT_PEM) >= 0) {
            if (!gnutls_x509_crt_get_dn(cert, issued_for, &issued_for_len)) {
              if (gnutls_x509_crt_export2(cert, GNUTLS_X509_FMT_PEM, &export_dat) >= 0) {
                j_return = json_pack("STR", export_dat.data, export_dat.size);
                gnutls_free(export_dat.data);
              } else {
                y_log_message(Y_LOG_LEVEL_ERROR, "STR");
                j_return = json_pack("STR", G_ERROR);
              }
            } else {
              y_log_message(Y_LOG_LEVEL_ERROR, "STR");
              j_return = json_pack("STR", G_ERROR);
            }
          } else {
            y_log_message(Y_LOG_LEVEL_ERROR, "STR");
            j_return = json_pack("STR", G_ERROR);
          }
        } else {
          y_log_message(Y_LOG_LEVEL_ERROR, "STR");
          j_return = json_pack("STR", G_ERROR);
        }
        gnutls_x509_crt_deinit(cert);
      }
    } else {
      y_log_message(Y_LOG_LEVEL_ERROR, "STR");
      j_return = json_pack("STR", G_ERROR_MEMORY);
    }
    o_free(cert_content);
    fclose(fl);
  } else {
    y_log_message(Y_LOG_LEVEL_ERROR, "STR", path);
    j_return = json_pack("STR", G_ERROR);
  }
  return j_return;
}