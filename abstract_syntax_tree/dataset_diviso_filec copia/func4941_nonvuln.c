static int proc_reg_open(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *pde = PDE(inode);
	int rv = 0;
	int (*open)(struct inode *, struct file *);
	int (*release)(struct inode *, struct file *);
	struct pde_opener *pdeo;

	
	pdeo = kmalloc(sizeof(struct pde_opener), GFP_KERNEL);
	if (!pdeo)
		return -ENOMEM;

	spin_lock(&pde->pde_unload_lock);
	if (!pde->proc_fops) {
		spin_unlock(&pde->pde_unload_lock);
		kfree(pdeo);
		return -ENOENT;
	}
	pde->pde_users++;
	open = pde->proc_fops->open;
	release = pde->proc_fops->release;
	spin_unlock(&pde->pde_unload_lock);

	if (open)
		rv = open(inode, file);

	spin_lock(&pde->pde_unload_lock);
	if (rv == 0 && release) {
		
		pdeo->inode = inode;
		pdeo->file = file;
		
		pdeo->release = release;
		list_add(&pdeo->lh, &pde->pde_openers);
	} else
		kfree(pdeo);
	__pde_users_dec(pde);
	spin_unlock(&pde->pde_unload_lock);
	return rv;
}