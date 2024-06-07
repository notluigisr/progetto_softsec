static int _regulator_disable(struct regulator_dev *rdev)
{
	int ret = 0;

	if (WARN(rdev->use_count <= 0,
		 "STR", rdev_get_name(rdev)))
		return -EIO;

	
	if (rdev->use_count == 1 &&
	    (rdev->constraints && !rdev->constraints->always_on)) {

		
		if (_regulator_can_change_status(rdev)) {
			ret = _regulator_do_disable(rdev);
			if (ret < 0) {
				rdev_err(rdev, "STR");
				return ret;
			}
			_notifier_call_chain(rdev, REGULATOR_EVENT_DISABLE,
					NULL);
		}

		rdev->use_count = 0;
	} else if (rdev->use_count > 1) {

		if (rdev->constraints &&
			(rdev->constraints->valid_ops_mask &
			REGULATOR_CHANGE_DRMS))
			drms_uA_update(rdev);

		rdev->use_count--;
	}

	return ret;
}