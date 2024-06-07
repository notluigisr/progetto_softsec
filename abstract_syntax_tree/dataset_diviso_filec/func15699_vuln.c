static int __init mbochs_dev_init(void)
{
	int ret = 0;

	ret = alloc_chrdev_region(&mbochs_devt, 0, MINORMASK + 1, MBOCHS_NAME);
	if (ret < 0) {
		pr_err("STR", ret);
		return ret;
	}
	cdev_init(&mbochs_cdev, &vd_fops);
	cdev_add(&mbochs_cdev, mbochs_devt, MINORMASK + 1);
	pr_info("STR", __func__, MAJOR(mbochs_devt));

	ret = mdev_register_driver(&mbochs_driver);
	if (ret)
		goto err_cdev;

	mbochs_class = class_create(THIS_MODULE, MBOCHS_CLASS_NAME);
	if (IS_ERR(mbochs_class)) {
		pr_err("STR");
		ret = PTR_ERR(mbochs_class);
		goto err_driver;
	}
	mbochs_dev.class = mbochs_class;
	mbochs_dev.release = mbochs_device_release;
	dev_set_name(&mbochs_dev, "STR", MBOCHS_NAME);

	ret = device_register(&mbochs_dev);
	if (ret)
		goto err_class;

	ret = mdev_register_device(&mbochs_dev, &mdev_fops);
	if (ret)
		goto err_device;

	return 0;

err_device:
	device_unregister(&mbochs_dev);
err_class:
	class_destroy(mbochs_class);
err_driver:
	mdev_unregister_driver(&mbochs_driver);
err_cdev:
	cdev_del(&mbochs_cdev);
	unregister_chrdev_region(mbochs_devt, MINORMASK + 1);
	return ret;
}