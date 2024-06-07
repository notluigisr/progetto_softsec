static int type_cclass_hash(type_cclass_key* key)
{
  int i, val;
  UChar *p;

  val = 0;

  p = (UChar* )&(key->enc);
  for (i = 0; i < (int )sizeof(key->enc); i++) {
    val = val * 997 + (int )*p++;
  }

  p = (UChar* )(&key->type);
  for (i = 0; i < (int )sizeof(key->type); i++) {
    val = val * 997 + (int )*p++;
  }

  val += key->not;
  return val + (val >> 5);
}