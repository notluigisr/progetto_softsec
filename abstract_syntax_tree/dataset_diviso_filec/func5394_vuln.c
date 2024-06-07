static ssize_t iotlb_dump_cr(struct omap_iommu *obj, struct cr_regs *cr,
			     char *buf)
{
	char *p = buf;

	
	p += sprintf(p, "STR", cr->cam, cr->ram,
					(cr->cam & MMU_CAM_P) ? 1 : 0);

	return p - buf;
}