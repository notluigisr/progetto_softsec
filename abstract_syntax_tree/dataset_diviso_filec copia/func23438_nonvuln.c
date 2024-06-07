UsbHubCtrlClearTTBuffer (
  IN USB_DEVICE           *HubDev,
  IN UINT8                Port,
  IN UINT16               DevAddr,
  IN UINT16               EpNum,
  IN UINT16               EpType
  )
{
  EFI_STATUS              Status;
  UINT16                  Value;

  
  
  
  Value = (UINT16) ((EpNum & 0x0F) | (DevAddr << 4) |
          ((EpType & 0x03) << 11) | ((EpNum & 0x80) << 15));

  Status = UsbCtrlRequest (
             HubDev,
             EfiUsbNoData,
             USB_REQ_TYPE_CLASS,
             USB_HUB_TARGET_PORT,
             USB_HUB_REQ_CLEAR_TT,
             Value,
             (UINT16) (Port + 1),
             NULL,
             0
             );

  return Status;
}