bool asn1_read_OctetString(struct asn1_data *data, TALLOC_CTX *mem_ctx, DATA_BLOB *blob)
{
	int len;
	ZERO_STRUCTP(blob);
	if (!asn1_start_tag(data, ASN1_OCTET_STRING)) return false;
	len = asn1_tag_remaining(data);
	if (len < 0) {
		data->has_error = true;
		return false;
	}
	*blob = data_blob_talloc(mem_ctx, NULL, len+1);
	if (!blob->data || blob->length < len) {
		data->has_error = true;
		return false;
	}
	if (!asn1_read(data, blob->data, len)) goto err;
	if (!asn1_end_tag(data)) goto err;
	blob->length--;
	blob->data[len] = 0;
	return true;

  err:

	data_blob_free(blob);
	*blob = data_blob_null;
	return false;
}