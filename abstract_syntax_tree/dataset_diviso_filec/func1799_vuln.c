HiiGetConfigRespInfo(
  IN CONST EFI_HII_DATABASE_PROTOCOL        *This
  )
{
  EFI_STATUS                          Status;
  HII_DATABASE_PRIVATE_DATA           *Private;
  EFI_STRING                          ConfigAltResp;
  UINTN                               ConfigSize;

  ConfigAltResp        = NULL;
  ConfigSize           = 0;

  Private = HII_DATABASE_DATABASE_PRIVATE_DATA_FROM_THIS (This);

  
  
  
  Status = HiiConfigRoutingExportConfig(&Private->ConfigRouting,&ConfigAltResp);

  if (!EFI_ERROR (Status)){
    ConfigSize = StrSize(ConfigAltResp);
    if (ConfigSize > gConfigRespSize){
      
      
      
      
      gConfigRespSize = ConfigSize + (ConfigSize >> 2);
      if (gRTConfigRespBuffer != NULL){
        FreePool(gRTConfigRespBuffer);
        DEBUG ((DEBUG_WARN, "STR"));
      }
      gRTConfigRespBuffer = (EFI_STRING) AllocateRuntimeZeroPool (gConfigRespSize);
      if (gRTConfigRespBuffer == NULL){
        FreePool(ConfigAltResp);
        DEBUG ((DEBUG_ERROR, "STR"));
        return EFI_OUT_OF_RESOURCES;
      }
    } else {
      ZeroMem(gRTConfigRespBuffer,gConfigRespSize);
    }
    CopyMem(gRTConfigRespBuffer,ConfigAltResp,ConfigSize);
    gBS->InstallConfigurationTable (&gEfiHiiConfigRoutingProtocolGuid, gRTConfigRespBuffer);
    FreePool(ConfigAltResp);
  }

  return EFI_SUCCESS;

}