con_insert_unipair(struct uni_pagedir *p, u_short unicode, u_short fontpos)
{
	int i, n;
	u16 **p1, *p2;

	p1 = p->uni_pgdir[n = unicode >> 11];
	if (!p1) {
		p1 = p->uni_pgdir[n] = kmalloc_array(32, sizeof(u16 *),
						     GFP_KERNEL);
		if (!p1) return -ENOMEM;
		for (i = 0; i < 32; i++)
			p1[i] = NULL;
	}

	p2 = p1[n = (unicode >> 6) & 0x1f];
	if (!p2) {
		p2 = p1[n] = kmalloc_array(64, sizeof(u16), GFP_KERNEL);
		if (!p2) {
			kfree(p1);
			p->uni_pgdir[n] = NULL;
			return -ENOMEM;
		}
		memset(p2, 0xff, 64*sizeof(u16)); 
	}

	p2[unicode & 0x3f] = fontpos;
	
	p->sum += (fontpos << 20) + unicode;

	return 0;
}