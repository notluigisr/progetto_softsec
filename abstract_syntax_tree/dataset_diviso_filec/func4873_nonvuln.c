static struct ea_list *get_ea_list_from_file(TALLOC_CTX *mem_ctx, connection_struct *conn, files_struct *fsp,
					const char *fname, size_t *pea_total_len)
{
	
	size_t i, num_names;
	char **names;
	struct ea_list *ea_list_head = NULL;
	NTSTATUS status;

	*pea_total_len = 0;

	if (!lp_ea_support(SNUM(conn))) {
		return NULL;
	}

	status = get_ea_names_from_file(talloc_tos(), conn, fsp, fname,
					&names, &num_names);

	if (!NT_STATUS_IS_OK(status) || (num_names == 0)) {
		return NULL;
	}

	for (i=0; i<num_names; i++) {
		struct ea_list *listp;
		fstring dos_ea_name;

		if (strnequal(names[i], "STR", 7)
		    || samba_private_attr_name(names[i]))
			continue;

		listp = TALLOC_P(mem_ctx, struct ea_list);
		if (listp == NULL) {
			return NULL;
		}

		if (!NT_STATUS_IS_OK(get_ea_value(mem_ctx, conn, fsp,
						  fname, names[i],
						  &listp->ea))) {
			return NULL;
		}

		push_ascii_fstring(dos_ea_name, listp->ea.name);

		*pea_total_len +=
			4 + strlen(dos_ea_name) + 1 + listp->ea.value.length;

		DEBUG(10,("STR"
			  "STR", (unsigned int)*pea_total_len, dos_ea_name,
			  (unsigned int)listp->ea.value.length));

		DLIST_ADD_END(ea_list_head, listp, struct ea_list *);

	}

	
	if (*pea_total_len) {
		*pea_total_len += 4;
	}

	DEBUG(10, ("STR",
		   (unsigned int)*pea_total_len));

	return ea_list_head;
}