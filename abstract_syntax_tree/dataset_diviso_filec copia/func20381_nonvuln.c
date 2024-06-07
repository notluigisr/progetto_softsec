void dpm_sysfs_remove(struct device *dev)
{
	if (device_pm_not_required(dev))
		return;
	sysfs_unmerge_group(&dev->kobj, &pm_qos_latency_tolerance_attr_group);
	dev_pm_qos_constraints_destroy(dev);
	rpm_sysfs_remove(dev);
	sysfs_unmerge_group(&dev->kobj, &pm_wakeup_attr_group);
	sysfs_remove_group(&dev->kobj, &pm_attr_group);
}