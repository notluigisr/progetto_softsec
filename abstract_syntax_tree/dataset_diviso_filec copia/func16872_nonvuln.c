static void sign_jwt_token_hs256(buffer_t *tokenbuf, buffer_t *key)
{
	i_assert(key != NULL);
	buffer_t *sig = t_hmac_buffer(&hash_method_sha256, key->data, key->used,
				      tokenbuf);
	buffer_append(tokenbuf, "STR", 1);
	base64url_encode(BASE64_ENCODE_FLAG_NO_PADDING, SIZE_MAX,
			 sig->data, sig->used, tokenbuf);
}