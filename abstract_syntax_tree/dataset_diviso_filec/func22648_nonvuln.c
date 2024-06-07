int Field_blob::key_cmp(const uchar *a,const uchar *b)
{
  return Field_blob::cmp(a+HA_KEY_BLOB_LENGTH, uint2korr(a),
			 b+HA_KEY_BLOB_LENGTH, uint2korr(b));
}