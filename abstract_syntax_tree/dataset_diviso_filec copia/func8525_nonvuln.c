SdMmcHcGetMaxCurrent (
  IN     EFI_PCI_IO_PROTOCOL  *PciIo,
  IN     UINT8                Slot,
     OUT UINT64               *MaxCurrent
  )
{
  EFI_STATUS          Status;

  Status = SdMmcHcRwMmio (PciIo, Slot, SD_MMC_HC_MAX_CURRENT_CAP, TRUE, sizeof (UINT64), MaxCurrent);

  return Status;
}