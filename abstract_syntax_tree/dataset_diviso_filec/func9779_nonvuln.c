static TEE_Result op_attr_bignum_to_user(void *attr,
					 struct tee_ta_session *sess,
					 void *buffer, uint64_t *size)
{
	TEE_Result res;
	struct bignum **bn = attr;
	uint64_t req_size;
	uint64_t s;

	res = tee_svc_copy_from_user(&s, size, sizeof(s));
	if (res != TEE_SUCCESS)
		return res;

	req_size = crypto_bignum_num_bytes(*bn);
	res = tee_svc_copy_to_user(size, &req_size, sizeof(req_size));
	if (res != TEE_SUCCESS)
		return res;
	if (!req_size)
		return TEE_SUCCESS;
	if (s < req_size || !buffer)
		return TEE_ERROR_SHORT_BUFFER;

	
	res = tee_mmu_check_access_rights(to_user_ta_ctx(sess->ctx),
					  TEE_MEMORY_ACCESS_READ |
					  TEE_MEMORY_ACCESS_WRITE |
					  TEE_MEMORY_ACCESS_ANY_OWNER,
					  (uaddr_t)buffer, req_size);
	if (res != TEE_SUCCESS)
		return res;
	
	crypto_bignum_bn2bin(*bn, buffer);
	return TEE_SUCCESS;
}