static ssize_t status_show_vhci(int pdev_nr, char *out)
{
	struct platform_device *pdev = vhcis[pdev_nr].pdev;
	struct vhci *vhci;
	struct usb_hcd *hcd;
	struct vhci_hcd *vhci_hcd;
	char *s = out;
	int i;
	unsigned long flags;

	if (!pdev || !out) {
		usbip_dbg_vhci_sysfs("STR");
		return 0;
	}

	hcd = platform_get_drvdata(pdev);
	vhci_hcd = hcd_to_vhci_hcd(hcd);
	vhci = vhci_hcd->vhci;

	spin_lock_irqsave(&vhci->lock, flags);

	for (i = 0; i < VHCI_HC_PORTS; i++) {
		struct vhci_device *vdev = &vhci->vhci_hcd_hs->vdev[i];

		spin_lock(&vdev->ud.lock);
		port_show_vhci(&out, HUB_SPEED_HIGH,
			       pdev_nr * VHCI_PORTS + i, vdev);
		spin_unlock(&vdev->ud.lock);
	}

	for (i = 0; i < VHCI_HC_PORTS; i++) {
		struct vhci_device *vdev = &vhci->vhci_hcd_ss->vdev[i];

		spin_lock(&vdev->ud.lock);
		port_show_vhci(&out, HUB_SPEED_SUPER,
			       pdev_nr * VHCI_PORTS + VHCI_HC_PORTS + i, vdev);
		spin_unlock(&vdev->ud.lock);
	}

	spin_unlock_irqrestore(&vhci->lock, flags);

	return out - s;
}