static struct ldb_message *winsdb_message(struct ldb_context *ldb,
					  struct winsdb_record *rec,
					  TALLOC_CTX *mem_ctx)
{
	int i, ret;
	size_t addr_count;
	const char *expire_time;
	struct ldb_message *msg = ldb_msg_new(mem_ctx);
	if (msg == NULL) goto failed;

	
	addr_count = winsdb_addr_list_length(rec->addresses);
	if (rec->state == WREPL_STATE_ACTIVE && addr_count == 0) {
		rec->state = WREPL_STATE_RELEASED;
	}
	if (rec->type == WREPL_TYPE_UNIQUE && addr_count > 1) {
		rec->type = WREPL_TYPE_MHOMED;
	}

	expire_time = ldb_timestring(msg, rec->expire_time);
	if (!expire_time) {
		goto failed;
	}

	msg->dn = winsdb_dn(msg, ldb, rec->name);
	if (msg->dn == NULL) goto failed;
	ret = ldb_msg_add_fmt(msg, "STR", rec->name->type);
	if (rec->name->name && *rec->name->name) {
		ret |= ldb_msg_add_string(msg, "STR", rec->name->name);
	}
	if (rec->name->scope && *rec->name->scope) {
		ret |= ldb_msg_add_string(msg, "STR", rec->name->scope);
	}
	ret |= ldb_msg_add_fmt(msg, "STR");
	ret |= ldb_msg_add_fmt(msg, "STR", rec->type);
	ret |= ldb_msg_add_fmt(msg, "STR", rec->state);
	ret |= ldb_msg_add_fmt(msg, "STR", rec->node);
	ret |= ldb_msg_add_fmt(msg, "STR", rec->is_static);
	ret |= ldb_msg_add_empty(msg, "STR", 0, NULL);
	if (!(rec->is_static && rec->state == WREPL_STATE_ACTIVE)) {
		ret |= ldb_msg_add_string(msg, "STR", expire_time);
	}
	ret |= ldb_msg_add_fmt(msg, "STR", (long long)rec->version);
	ret |= ldb_msg_add_string(msg, "STR", rec->wins_owner);
	ret |= ldb_msg_add_empty(msg, "STR", 0, NULL);
	for (i=0;rec->addresses[i];i++) {
		ret |= ldb_msg_add_winsdb_addr(msg, rec, "STR", rec->addresses[i]);
	}
	if (rec->registered_by) {
		ret |= ldb_msg_add_empty(msg, "STR", 0, NULL);
		ret |= ldb_msg_add_string(msg, "STR", rec->registered_by);
	}
	if (ret != LDB_SUCCESS) goto failed;
	return msg;

failed:
	talloc_free(msg);
	return NULL;
}