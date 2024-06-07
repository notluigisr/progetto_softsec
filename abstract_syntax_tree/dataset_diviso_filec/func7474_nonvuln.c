static int cqspi_of_get_pdata(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct cqspi_st *cqspi = platform_get_drvdata(pdev);

	cqspi->is_decoded_cs = of_property_read_bool(np, "STR");

	if (of_property_read_u32(np, "STR", &cqspi->fifo_depth)) {
		dev_err(&pdev->dev, "STR");
		return -ENXIO;
	}

	if (of_property_read_u32(np, "STR", &cqspi->fifo_width)) {
		dev_err(&pdev->dev, "STR");
		return -ENXIO;
	}

	if (of_property_read_u32(np, "STR",
				 &cqspi->trigger_address)) {
		dev_err(&pdev->dev, "STR");
		return -ENXIO;
	}

	return 0;
}