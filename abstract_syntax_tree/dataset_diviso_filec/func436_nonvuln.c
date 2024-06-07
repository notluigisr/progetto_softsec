PeiHubSetPortFeature (
  IN EFI_PEI_SERVICES    **PeiServices,
  IN PEI_USB_IO_PPI      *UsbIoPpi,
  IN UINT8               Port,
  IN UINT8               Value
  )
{
  EFI_USB_DEVICE_REQUEST      DeviceRequest;

  ZeroMem (&DeviceRequest, sizeof (EFI_USB_DEVICE_REQUEST));

  
  
  
  DeviceRequest.RequestType = USB_HUB_SET_PORT_FEATURE_REQ_TYPE;
  DeviceRequest.Request     = USB_HUB_SET_PORT_FEATURE;
  DeviceRequest.Value       = Value;
  DeviceRequest.Index       = Port;

  return UsbIoPpi->UsbControlTransfer (
                     PeiServices,
                     UsbIoPpi,
                     &DeviceRequest,
                     EfiUsbNoData,
                     PcdGet32 (PcdUsbTransferTimeoutValue),
                     NULL,
                     0
                     );
}