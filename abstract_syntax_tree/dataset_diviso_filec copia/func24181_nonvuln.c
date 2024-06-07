int samdb_msg_add_dom_sid(struct ldb_context *sam_ldb, TALLOC_CTX *mem_ctx, struct ldb_message *msg,
			  const char *attr_name, const struct dom_sid *sid)
{
	struct ldb_val v;
	enum ndr_err_code ndr_err;

	ndr_err = ndr_push_struct_blob(&v, mem_ctx, 
				       sid,
				       (ndr_push_flags_fn_t)ndr_push_dom_sid);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		return ldb_operr(sam_ldb);
	}
	return ldb_msg_add_value(msg, attr_name, &v, NULL);
}