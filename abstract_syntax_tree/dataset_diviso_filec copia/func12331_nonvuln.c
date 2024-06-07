GenerateHiiDatabaseRecord (
  IN  HII_DATABASE_PRIVATE_DATA *Private,
  OUT HII_DATABASE_RECORD       **DatabaseNode
  )
{
  HII_DATABASE_RECORD                *DatabaseRecord;
  HII_DATABASE_PACKAGE_LIST_INSTANCE *PackageList;
  HII_HANDLE                         *HiiHandle;

  if (Private == NULL || DatabaseNode == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  DatabaseRecord = (HII_DATABASE_RECORD *) AllocateZeroPool (sizeof (HII_DATABASE_RECORD));
  if (DatabaseRecord == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  DatabaseRecord->Signature = HII_DATABASE_RECORD_SIGNATURE;

  DatabaseRecord->PackageList = AllocateZeroPool (sizeof (HII_DATABASE_PACKAGE_LIST_INSTANCE));
  if (DatabaseRecord->PackageList == NULL) {
    FreePool (DatabaseRecord);
    return EFI_OUT_OF_RESOURCES;
  }

  PackageList = DatabaseRecord->PackageList;

  InitializeListHead (&PackageList->GuidPkgHdr);
  InitializeListHead (&PackageList->FormPkgHdr);
  InitializeListHead (&PackageList->KeyboardLayoutHdr);
  InitializeListHead (&PackageList->StringPkgHdr);
  InitializeListHead (&PackageList->FontPkgHdr);
  InitializeListHead (&PackageList->SimpleFontPkgHdr);
  PackageList->ImagePkg      = NULL;
  PackageList->DevicePathPkg = NULL;

  
  
  
  HiiHandle = (HII_HANDLE *) AllocateZeroPool (sizeof (HII_HANDLE));
  if (HiiHandle == NULL) {
    FreePool (DatabaseRecord->PackageList);
    FreePool (DatabaseRecord);
    return EFI_OUT_OF_RESOURCES;
  }
  HiiHandle->Signature = HII_HANDLE_SIGNATURE;
  
  
  
  Private->HiiHandleCount++;
  HiiHandle->Key = (UINTN) Private->HiiHandleCount;
  
  
  
  InsertTailList (&Private->HiiHandleList, &HiiHandle->Handle);

  DatabaseRecord->Handle = (EFI_HII_HANDLE) HiiHandle;

  
  
  
  InsertTailList (&Private->DatabaseList, &DatabaseRecord->DatabaseEntry);

  *DatabaseNode = DatabaseRecord;

  return EFI_SUCCESS;

}