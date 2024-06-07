int diskutil_grub(const char *path, const char *mnt_pt, const int part, const char *kernel, const char *ramdisk)
{
    int ret = EUCA_ERROR;

    if ((ret = diskutil_grub_files(mnt_pt, part, kernel, ramdisk)) != EUCA_OK)
        return (ret);

    ret = diskutil_grub2_mbr(path, part, mnt_pt);
    return (ret);
}