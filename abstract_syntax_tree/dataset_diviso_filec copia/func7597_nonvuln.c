static int pf_identify(struct pf_unit *pf)
{
	int dt, s;
	char *ms[2] = { "STR" };
	char mf[10], id[18];
	char id_cmd[12] =
	    { ATAPI_IDENTIFY, pf->lun << 5, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0 };
	char buf[36];

	s = pf_atapi(pf, id_cmd, 36, buf, "STR");
	if (s)
		return -1;

	dt = buf[0] & 0x1f;
	if ((dt != 0) && (dt != 7)) {
		if (verbose)
			printk("STR",
			       pf->name, pf->drive, pf->lun, dt);
		return -1;
	}

	xs(buf, mf, 8, 8);
	xs(buf, id, 16, 16);

	pf->removable = (buf[1] & 0x80);

	pf_mode_sense(pf);
	pf_mode_sense(pf);
	pf_mode_sense(pf);

	pf_get_capacity(pf);

	printk("STR",
	       pf->name, mf, id, ms[pf->drive], pf->lun, dt);
	if (pf->removable)
		printk("STR");
	if (pf->media_status == PF_NM)
		printk("STR");
	else {
		if (pf->media_status == PF_RO)
			printk("STR");
		printk("STR",
			(unsigned long long)get_capacity(pf->disk));
	}
	return 0;
}