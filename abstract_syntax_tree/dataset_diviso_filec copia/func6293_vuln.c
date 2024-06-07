PeiGetHubDescriptor (
  IN  EFI_PEI_SERVICES          **PeiServices,
  IN  PEI_USB_IO_PPI            *UsbIoPpi,
  IN  UINTN                     DescriptorSize,
  OUT EFI_USB_HUB_DESCRIPTOR    *HubDescriptor
  )
{
  EFI_USB_DEVICE_REQUEST      DevReq;
  ZeroMem (&DevReq, sizeof (EFI_USB_DEVICE_REQUEST));

  
  
  
  DevReq.RequestType = USB_RT_HUB | 0x80;
  DevReq.Request     = USB_HUB_GET_DESCRIPTOR;
  DevReq.Value       = USB_DT_HUB << 8;
  DevReq.Length      = (UINT16)DescriptorSize;

  return  UsbIoPpi->UsbControlTransfer (
                      PeiServices,
                      UsbIoPpi,
                      &DevReq,
                      EfiUsbDataIn,
                      PcdGet32 (PcdUsbTransferTimeoutValue),
                      HubDescriptor,
                      (UINT16)DescriptorSize
                      );
}