static u8 service_to_dlpipe(u16 service_id)
{
	switch (service_id) {
	case WMI_CONTROL_SVC:
		return 3;
	case WMI_BEACON_SVC:
	case WMI_CAB_SVC:
	case WMI_UAPSD_SVC:
	case WMI_MGMT_SVC:
	case WMI_DATA_VO_SVC:
	case WMI_DATA_VI_SVC:
	case WMI_DATA_BE_SVC:
	case WMI_DATA_BK_SVC:
		return 2;
	default:
		return 0;
	}
}