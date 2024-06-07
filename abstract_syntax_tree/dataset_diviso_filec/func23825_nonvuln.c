construct_cipher_name(SSL *ssl)
{
static uschar cipherbuf[256];

const SSL_CIPHER *c;
uschar *ver;

switch (ssl->session->ssl_version)
  {
  case SSL2_VERSION:
  ver = US"STR";
  break;

  case SSL3_VERSION:
  ver = US"STR";
  break;

  case TLS1_VERSION:
  ver = US"STR";
  break;

#ifdef TLS1_1_VERSION
  case TLS1_1_VERSION:
  ver = US"STR";
  break;
#endif

#ifdef TLS1_2_VERSION
  case TLS1_2_VERSION:
  ver = US"STR";
  break;
#endif

  default:
  ver = US"STR";
  }

c = (const SSL_CIPHER *) SSL_get_current_cipher(ssl);
SSL_CIPHER_get_bits(c, &tls_bits);

string_format(cipherbuf, sizeof(cipherbuf), "STR", ver,
  SSL_CIPHER_get_name(c), tls_bits);
tls_cipher = cipherbuf;

DEBUG(D_tls) debug_printf("STR", cipherbuf);
}