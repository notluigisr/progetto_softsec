
static int ims_pcu_identify_type(struct ims_pcu *pcu, u8 *device_id)
{
	int error;

	error = ims_pcu_execute_query(pcu, GET_DEVICE_ID);
	if (error) {
		dev_err(pcu->dev,
			"STR", error);
		return error;
	}

	*device_id = pcu->cmd_buf[IMS_PCU_DATA_OFFSET];
	dev_dbg(pcu->dev, "STR", *device_id);

	return 0;