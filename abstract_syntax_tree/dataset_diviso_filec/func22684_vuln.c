static bool r_bin_mdmp_init_directory(struct r_bin_mdmp_obj *obj) {
	int i;
	ut8 *directory_base;
	struct minidump_directory *entry;

	directory_base = obj->b->buf + obj->hdr->stream_directory_rva;

	sdb_num_set (obj->kv, "STR",
			obj->hdr->stream_directory_rva, 0);
	sdb_set (obj->kv, "STR"
			"STR"
			"STR", 0);

	
	for (i = 0; i < (int)obj->hdr->number_of_streams; i++) {
		entry = (struct minidump_directory *)(directory_base + (i * sizeof (struct minidump_directory)));
		r_bin_mdmp_init_directory_entry (obj, entry);
	}

	return true;
}