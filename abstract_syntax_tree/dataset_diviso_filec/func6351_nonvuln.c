b64enc_start (struct b64state *state, FILE *fp, const char *title)
{
  return enc_start (state, fp, NULL, title);
}