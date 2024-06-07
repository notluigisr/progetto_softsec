SupportUdfFileSystem (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle
  )
{
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL  *LastDevicePathNode;
  EFI_GUID                  *VendorDefinedGuid;

  
  
  
  Status = gBS->OpenProtocol (
    ControllerHandle,
    &gEfiDevicePathProtocolGuid,
    (VOID **)&DevicePath,
    This->DriverBindingHandle,
    ControllerHandle,
    EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  Status = EFI_UNSUPPORTED;

  
  
  
  LastDevicePathNode = NULL;
  DevicePathNode = DevicePath;
  while (!IsDevicePathEnd (DevicePathNode)) {
    LastDevicePathNode = DevicePathNode;
    DevicePathNode = NextDevicePathNode (DevicePathNode);
  }
  
  
  
  
  if (LastDevicePathNode != NULL &&
      DevicePathType (LastDevicePathNode) == MEDIA_DEVICE_PATH &&
      DevicePathSubType (LastDevicePathNode) == MEDIA_VENDOR_DP) {
    VendorDefinedGuid = (EFI_GUID *)((UINTN)LastDevicePathNode +
                                     OFFSET_OF (VENDOR_DEVICE_PATH, Guid));
    if (CompareGuid (VendorDefinedGuid, &gUdfDevPathGuid)) {
      Status = EFI_SUCCESS;
    }
  }

  
  
  
  gBS->CloseProtocol (
    ControllerHandle,
    &gEfiDevicePathProtocolGuid,
    This->DriverBindingHandle,
    ControllerHandle
    );

  return Status;
}