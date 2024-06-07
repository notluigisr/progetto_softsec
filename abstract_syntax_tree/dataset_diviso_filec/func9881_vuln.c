UsbHubReadDesc (
  IN  USB_DEVICE              *HubDev,
  OUT EFI_USB_HUB_DESCRIPTOR  *HubDesc
  )
{
  EFI_STATUS              Status;

  if (HubDev->Speed == EFI_USB_SPEED_SUPER) {
    
    
    
    Status = UsbHubCtrlGetSuperSpeedHubDesc (HubDev, HubDesc);
  } else {

    
    
    
    Status = UsbHubCtrlGetHubDesc (HubDev, HubDesc, 2);

    if (EFI_ERROR (Status)) {
      return Status;
    }

    
    
    
    Status = UsbHubCtrlGetHubDesc (HubDev, HubDesc, HubDesc->Length);
  }

  return Status;
}