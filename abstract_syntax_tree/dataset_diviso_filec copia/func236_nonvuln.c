SaveBootScriptDataToLockBox (
  VOID
  )
{
  EFI_STATUS            Status;

  
  
  
  
  Status = SaveLockBox (
             &mBootScriptDataGuid,
             (VOID *)mS3BootScriptTablePtr->TableBase,
             EFI_PAGES_TO_SIZE (mS3BootScriptTablePtr->TableMemoryPageNumber)
             );
  ASSERT_EFI_ERROR (Status);

  Status = SetLockBoxAttributes (&mBootScriptDataGuid, LOCK_BOX_ATTRIBUTE_RESTORE_IN_PLACE);
  ASSERT_EFI_ERROR (Status);

  
  
  
  
  Status = SaveLockBox (
             &mBootScriptTableBaseGuid,
             (VOID *)&mS3BootScriptTablePtr->TableBase,
             sizeof(mS3BootScriptTablePtr->TableBase)
             );
  ASSERT_EFI_ERROR (Status);

  Status = SetLockBoxAttributes (&mBootScriptTableBaseGuid, LOCK_BOX_ATTRIBUTE_RESTORE_IN_PLACE);
  ASSERT_EFI_ERROR (Status);
}