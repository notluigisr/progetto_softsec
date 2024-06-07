HiiGetDatabaseInfo(
  IN CONST EFI_HII_DATABASE_PROTOCOL        *This
  )
{
  EFI_STATUS                          Status;
  EFI_HII_PACKAGE_LIST_HEADER         *DatabaseInfo;
  UINTN                               DatabaseInfoSize;

  DatabaseInfo         = NULL;
  DatabaseInfoSize     = 0;

  
  
  
  Status = HiiExportPackageLists(This, NULL, &DatabaseInfoSize, DatabaseInfo);

  ASSERT(Status == EFI_BUFFER_TOO_SMALL);

  if(DatabaseInfoSize > gDatabaseInfoSize ) {
    
    
    
    
    gDatabaseInfoSize = DatabaseInfoSize + (DatabaseInfoSize >> 2);
    if (gRTDatabaseInfoBuffer != NULL){
      FreePool(gRTDatabaseInfoBuffer);
      DEBUG ((DEBUG_WARN, "STR"));
    }
    gRTDatabaseInfoBuffer = AllocateRuntimeZeroPool (gDatabaseInfoSize);
    if (gRTDatabaseInfoBuffer == NULL){
      DEBUG ((DEBUG_ERROR, "STR"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    ZeroMem(gRTDatabaseInfoBuffer,gDatabaseInfoSize);
  }
  Status = HiiExportPackageLists(This, NULL, &DatabaseInfoSize, gRTDatabaseInfoBuffer);
  ASSERT_EFI_ERROR (Status);
  gBS->InstallConfigurationTable (&gEfiHiiDatabaseProtocolGuid, gRTDatabaseInfoBuffer);

  return EFI_SUCCESS;

}