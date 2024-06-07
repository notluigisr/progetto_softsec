PeiUsbHubReadDesc (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN PEI_USB_DEVICE             *PeiUsbDevice,
  IN PEI_USB_IO_PPI             *UsbIoPpi,
  OUT EFI_USB_HUB_DESCRIPTOR    *HubDescriptor
  )
{
  EFI_STATUS Status;

  if (PeiUsbDevice->DeviceSpeed == EFI_USB_SPEED_SUPER) {
    
    
    
    Status = PeiGetSuperSpeedHubDesc (PeiServices, UsbIoPpi, HubDescriptor);
  } else {

    
    
    
    Status = PeiGetHubDescriptor (PeiServices, UsbIoPpi, 2, HubDescriptor);

    if (EFI_ERROR (Status)) {
      return Status;
    }

    
    
    
    Status = PeiGetHubDescriptor (PeiServices, UsbIoPpi, HubDescriptor->Length, HubDescriptor);
  }

  return Status;
}