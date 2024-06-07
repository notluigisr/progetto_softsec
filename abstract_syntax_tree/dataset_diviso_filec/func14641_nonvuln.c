static void add_sect_attrs(struct module *mod, const struct load_info *info)
{
	unsigned int nloaded = 0, i, size[2];
	struct module_sect_attrs *sect_attrs;
	struct module_sect_attr *sattr;
	struct bin_attribute **gattr;

	
	for (i = 0; i < info->hdr->e_shnum; i++)
		if (!sect_empty(&info->sechdrs[i]))
			nloaded++;
	size[0] = ALIGN(struct_size(sect_attrs, attrs, nloaded),
			sizeof(sect_attrs->grp.bin_attrs[0]));
	size[1] = (nloaded + 1) * sizeof(sect_attrs->grp.bin_attrs[0]);
	sect_attrs = kzalloc(size[0] + size[1], GFP_KERNEL);
	if (sect_attrs == NULL)
		return;

	
	sect_attrs->grp.name = "STR";
	sect_attrs->grp.bin_attrs = (void *)sect_attrs + size[0];

	sect_attrs->nsections = 0;
	sattr = &sect_attrs->attrs[0];
	gattr = &sect_attrs->grp.bin_attrs[0];
	for (i = 0; i < info->hdr->e_shnum; i++) {
		Elf_Shdr *sec = &info->sechdrs[i];
		if (sect_empty(sec))
			continue;
		sysfs_bin_attr_init(&sattr->battr);
		sattr->address = sec->sh_addr;
		sattr->battr.attr.name =
			kstrdup(info->secstrings + sec->sh_name, GFP_KERNEL);
		if (sattr->battr.attr.name == NULL)
			goto out;
		sect_attrs->nsections++;
		sattr->battr.read = module_sect_read;
		sattr->battr.size = MODULE_SECT_READ_SIZE;
		sattr->battr.attr.mode = 0400;
		*(gattr++) = &(sattr++)->battr;
	}
	*gattr = NULL;

	if (sysfs_create_group(&mod->mkobj.kobj, &sect_attrs->grp))
		goto out;

	mod->sect_attrs = sect_attrs;
	return;
  out:
	free_sect_attrs(sect_attrs);
}