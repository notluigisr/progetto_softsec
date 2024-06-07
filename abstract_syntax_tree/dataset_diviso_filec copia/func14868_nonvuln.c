create_la_entry(struct replmd_private *replmd_private,
		struct drsuapi_DsReplicaLinkedAttribute *la,
		uint32_t dsdb_repl_flags)
{
	struct la_entry *la_entry;

	if (replmd_private->la_ctx == NULL) {
		replmd_private->la_ctx = talloc_new(replmd_private);
	}
	la_entry = talloc(replmd_private->la_ctx, struct la_entry);
	if (la_entry == NULL) {
		return NULL;
	}
	la_entry->la = talloc(la_entry,
			      struct drsuapi_DsReplicaLinkedAttribute);
	if (la_entry->la == NULL) {
		talloc_free(la_entry);
		return NULL;
	}
	*la_entry->la = *la;
	la_entry->dsdb_repl_flags = dsdb_repl_flags;

	
	talloc_steal(la_entry->la, la_entry->la->identifier);
	talloc_steal(la_entry->la, la_entry->la->value.blob);

	return la_entry;
}