static int platform_drv_probe(struct device *_dev)
{
	struct platform_driver *drv = to_platform_driver(_dev->driver);
	struct platform_device *dev = to_platform_device(_dev);
	int ret;

	ret = of_clk_set_defaults(_dev->of_node, false);
	if (ret < 0)
		return ret;

	ret = dev_pm_domain_attach(_dev, true);
	if (ret != -EPROBE_DEFER) {
		if (drv->probe) {
			ret = drv->probe(dev);
			if (ret)
				dev_pm_domain_detach(_dev, true);
		} else {
			
			ret = 0;
		}
	}

	if (drv->prevent_deferred_probe && ret == -EPROBE_DEFER) {
		dev_warn(_dev, "STR");
		ret = -ENXIO;
	}

	return ret;
}