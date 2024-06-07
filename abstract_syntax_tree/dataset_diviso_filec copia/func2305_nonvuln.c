SdMmcHcInitHost (
  IN SD_MMC_HC_PRIVATE_DATA *Private,
  IN UINT8                  Slot
  )
{
  EFI_STATUS                Status;
  EFI_PCI_IO_PROTOCOL       *PciIo;
  SD_MMC_HC_SLOT_CAP        Capability;

  
  
  
  
  if (mOverride != NULL && mOverride->NotifyPhase != NULL) {
    Status = mOverride->NotifyPhase (
                          Private->ControllerHandle,
                          Slot,
                          EdkiiSdMmcInitHostPre,
                          NULL);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_WARN,
        "STR",
        __FUNCTION__, Status));
      return Status;
    }
  }

  PciIo = Private->PciIo;
  Capability = Private->Capability[Slot];

  Status = SdMmcHcInitV4Enhancements (PciIo, Slot, Capability, Private->ControllerVersion[Slot]);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  
  
  
  
  
  
  
  Status = SdMmcHcClockSupply (Private, Slot, 0, TRUE, 400);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = SdMmcHcInitPowerVoltage (PciIo, Slot, Capability);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = SdMmcHcInitTimeoutCtrl (PciIo, Slot);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  
  
  
  
  if (mOverride != NULL && mOverride->NotifyPhase != NULL) {
    Status = mOverride->NotifyPhase (
                          Private->ControllerHandle,
                          Slot,
                          EdkiiSdMmcInitHostPost,
                          NULL);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_WARN,
        "STR",
        __FUNCTION__, Status));
    }
  }
  return Status;
}