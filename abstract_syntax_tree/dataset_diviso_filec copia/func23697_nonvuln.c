static GuestDiskAddressList *build_guest_disk_info(char *guid, Error **errp)
{
    GuestDiskAddressList *list = NULL;
    GuestDiskAddress *disk;
    SCSI_ADDRESS addr, *scsi_ad;
    DWORD len;
    int bus;
    HANDLE vol_h;

    scsi_ad = &addr;
    char *name = g_strndup(guid, strlen(guid)-1);

    vol_h = CreateFile(name, 0, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                       0, NULL);
    if (vol_h == INVALID_HANDLE_VALUE) {
        error_setg_win32(errp, GetLastError(), "STR");
        goto out_free;
    }

    bus = get_disk_bus_type(vol_h, errp);
    if (bus < 0) {
        goto out_close;
    }

    disk = g_malloc0(sizeof(*disk));
    disk->bus_type = find_bus_type(bus);
    if (bus == BusTypeScsi || bus == BusTypeAta || bus == BusTypeRAID
#if (_WIN32_WINNT >= 0x0600)
            
            || bus == BusTypeSas
#endif
        ) {
        
    } else {
         disk->pci_controller = NULL;
    }

    list = g_malloc0(sizeof(*list));
    list->value = disk;
    list->next = NULL;
out_close:
    CloseHandle(vol_h);
out_free:
    g_free(name);
    return list;
}