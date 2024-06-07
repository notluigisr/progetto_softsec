PeiDoHubConfig (
  IN EFI_PEI_SERVICES    **PeiServices,
  IN PEI_USB_DEVICE      *PeiUsbDevice
  )
{
  EFI_USB_HUB_DESCRIPTOR  HubDescriptor;
  EFI_STATUS              Status;
  EFI_USB_HUB_STATUS      HubStatus;
  UINTN                   Index;
  PEI_USB_IO_PPI          *UsbIoPpi;

  ZeroMem (&HubDescriptor, sizeof (HubDescriptor));
  UsbIoPpi = &PeiUsbDevice->UsbIoPpi;

  
  
  
  Status = PeiUsbHubReadDesc (
            PeiServices,
            PeiUsbDevice,
            UsbIoPpi,
            &HubDescriptor
            );
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  PeiUsbDevice->DownStreamPortNo = HubDescriptor.NbrPorts;

  if (PeiUsbDevice->DeviceSpeed == EFI_USB_SPEED_SUPER) {
    DEBUG ((EFI_D_INFO, "STR", PeiUsbDevice->Tier));
    PeiUsbHubCtrlSetHubDepth (
      PeiServices,
      PeiUsbDevice,
      UsbIoPpi
      );
  } else {
    
    
    
    for (Index = 0; Index < PeiUsbDevice->DownStreamPortNo; Index++) {
      Status = PeiHubSetPortFeature (
                PeiServices,
                UsbIoPpi,
                (UINT8) (Index + 1),
                EfiUsbPortPower
                );
      if (EFI_ERROR (Status)) {
        DEBUG (( EFI_D_ERROR, "STR", Index));
        continue;
      }
    }

    DEBUG (( EFI_D_INFO, "STR", HubDescriptor.PwrOn2PwrGood));
    if (HubDescriptor.PwrOn2PwrGood > 0) {
      MicroSecondDelay (HubDescriptor.PwrOn2PwrGood * USB_SET_PORT_POWER_STALL);
    }

    
    
    
    Status = PeiHubGetHubStatus (
              PeiServices,
              UsbIoPpi,
              (UINT32 *) &HubStatus
              );
    if (EFI_ERROR (Status)) {
      return EFI_DEVICE_ERROR;
    } else {
      
      
      
      if ((HubStatus.HubChangeStatus & HUB_CHANGE_LOCAL_POWER) != 0) {
        PeiHubClearHubFeature (
          PeiServices,
          UsbIoPpi,
          C_HUB_LOCAL_POWER
          );
      }
      
      
      
      if ((HubStatus.HubChangeStatus & HUB_CHANGE_OVERCURRENT) != 0) {
        PeiHubClearHubFeature (
          PeiServices,
          UsbIoPpi,
          C_HUB_OVER_CURRENT
          );
      }
    }
  }

  return EFI_SUCCESS;
}