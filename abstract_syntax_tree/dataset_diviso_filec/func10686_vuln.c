CpuMpPeimInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS           Status;
  EFI_VECTOR_HANDOFF_INFO         *VectorInfo;
  EFI_PEI_VECTOR_HANDOFF_INFO_PPI *VectorHandoffInfoPpi;

  
  
  
  VectorInfo = NULL;
  Status = PeiServicesLocatePpi (
             &gEfiVectorHandoffInfoPpiGuid,
             0,
             NULL,
             (VOID **)&VectorHandoffInfoPpi
             );
  if (Status == EFI_SUCCESS) {
    VectorInfo = VectorHandoffInfoPpi->Info;
  }
  Status = InitializeCpuExceptionHandlers (VectorInfo);
  ASSERT_EFI_ERROR (Status);

  
  
  
  Status = MpInitLibInitialize ();
  ASSERT_EFI_ERROR (Status);

  
  
  
  CollectBistDataFromPpi (PeiServices);

  
  
  
  Status = PeiServicesInstallPpi(&mPeiCpuMpPpiDesc);
  ASSERT_EFI_ERROR (Status);

  return Status;
}