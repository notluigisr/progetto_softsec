bj10v_open(gx_device * pdev)
{
    if (pdev->HWResolution[0] < 180 ||
        pdev->HWResolution[1] < 180)
    {
        emprintf("STR");
        return_error(gs_error_rangecheck);
    }
    return gdev_prn_open(pdev);
}