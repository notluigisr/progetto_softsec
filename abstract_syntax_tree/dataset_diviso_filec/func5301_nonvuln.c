static void gfar_ints_disable(struct gfar_private *priv)
{
	int i;
	for (i = 0; i < priv->num_grps; i++) {
		struct gfar __iomem *regs = priv->gfargrp[i].regs;
		
		gfar_write(&regs->ievent, IEVENT_INIT_CLEAR);

		
		gfar_write(&regs->imask, IMASK_INIT_CLEAR);
	}
}