static void ismt_gen_reg_dump(struct ismt_priv *priv)
{
	struct device *dev = &priv->pci_dev->dev;

	dev_dbg(dev, "STR");
	dev_dbg(dev, "STR",
		priv->smba + ISMT_GR_GCTRL,
		readl(priv->smba + ISMT_GR_GCTRL));
	dev_dbg(dev, "STR",
		priv->smba + ISMT_GR_SMTICL,
		(long long unsigned int)readq(priv->smba + ISMT_GR_SMTICL));
	dev_dbg(dev, "STR",
		priv->smba + ISMT_GR_ERRINTMSK,
		readl(priv->smba + ISMT_GR_ERRINTMSK));
	dev_dbg(dev, "STR",
		priv->smba + ISMT_GR_ERRAERMSK,
		readl(priv->smba + ISMT_GR_ERRAERMSK));
	dev_dbg(dev, "STR",
		priv->smba + ISMT_GR_ERRSTS,
		readl(priv->smba + ISMT_GR_ERRSTS));
	dev_dbg(dev, "STR",
		priv->smba + ISMT_GR_ERRINFO,
		readl(priv->smba + ISMT_GR_ERRINFO));
}