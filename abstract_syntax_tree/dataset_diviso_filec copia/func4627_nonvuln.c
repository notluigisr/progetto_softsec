static TEE_Result tee_svc_cipher_update_helper(unsigned long state,
			bool last_block, const void *src, size_t src_len,
			void *dst, uint64_t *dst_len)
{
	TEE_Result res;
	struct tee_cryp_state *cs;
	struct tee_ta_session *sess;
	uint64_t dlen;

	res = tee_ta_get_current_session(&sess);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_svc_cryp_get_state(sess, tee_svc_uref_to_vaddr(state), &cs);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_mmu_check_access_rights(to_user_ta_ctx(sess->ctx),
					  TEE_MEMORY_ACCESS_READ |
					  TEE_MEMORY_ACCESS_ANY_OWNER,
					  (uaddr_t)src, src_len);
	if (res != TEE_SUCCESS)
		return res;

	if (!dst_len) {
		dlen = 0;
	} else {
		res = tee_svc_copy_from_user(&dlen, dst_len, sizeof(dlen));
		if (res != TEE_SUCCESS)
			return res;

		res = tee_mmu_check_access_rights(to_user_ta_ctx(sess->ctx),
						  TEE_MEMORY_ACCESS_READ |
						  TEE_MEMORY_ACCESS_WRITE |
						  TEE_MEMORY_ACCESS_ANY_OWNER,
						  (uaddr_t)dst, dlen);
		if (res != TEE_SUCCESS)
			return res;
	}

	if (dlen < src_len) {
		res = TEE_ERROR_SHORT_BUFFER;
		goto out;
	}

	if (src_len > 0) {
		
		res = tee_do_cipher_update(cs->ctx, cs->algo, cs->mode,
					   last_block, src, src_len, dst);
	}

	if (last_block && cs->ctx_finalize != NULL) {
		cs->ctx_finalize(cs->ctx, cs->algo);
		cs->ctx_finalize = NULL;
	}

out:
	if ((res == TEE_SUCCESS || res == TEE_ERROR_SHORT_BUFFER) &&
	    dst_len != NULL) {
		TEE_Result res2;

		dlen = src_len;
		res2 = tee_svc_copy_to_user(dst_len, &dlen, sizeof(*dst_len));
		if (res2 != TEE_SUCCESS)
			res = res2;
	}

	return res;
}