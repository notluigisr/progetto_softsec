struct ldb_val ldb_val_map_local(struct ldb_module *module, void *mem_ctx, 
				 const struct ldb_map_attribute *map, const struct ldb_val *val)
{
	if (map && (map->type == LDB_MAP_CONVERT) && (map->u.convert.convert_local)) {
		return map->u.convert.convert_local(module, mem_ctx, val);
	}

	return ldb_val_dup(mem_ctx, val);
}