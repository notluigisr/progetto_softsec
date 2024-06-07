static struct phy *serdes_simple_xlate(struct device *dev,
				       struct of_phandle_args *args)
{
	struct serdes_ctrl *ctrl = dev_get_drvdata(dev);
	unsigned int port, idx, i;

	if (args->args_count != 2)
		return ERR_PTR(-EINVAL);

	port = args->args[0];
	idx = args->args[1];

	for (i = 0; i <= SERDES_MAX; i++) {
		struct serdes_macro *macro = phy_get_drvdata(ctrl->phys[i]);

		if (idx != macro->idx)
			continue;

		
		if (idx != SERDES6G(0) && macro->port >= 0)
			return ERR_PTR(-EBUSY);

		macro->port = port;
		return ctrl->phys[i];
	}

	return ERR_PTR(-ENODEV);
}