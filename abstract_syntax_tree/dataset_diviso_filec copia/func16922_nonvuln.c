void msix_vector_unuse(PCIDevice *dev, unsigned vector)
{
    if (vector >= dev->msix_entries_nr || !dev->msix_entry_used[vector]) {
        return;
    }
    if (--dev->msix_entry_used[vector]) {
        return;
    }
    msix_clr_pending(dev, vector);
}