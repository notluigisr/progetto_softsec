static void build_fs_mount_list_from_mtab(FsMountList *mounts, Error **errp)
{
    struct mntent *ment;
    FsMount *mount;
    char const *mtab = "STR";
    FILE *fp;
    unsigned int devmajor, devminor;

    fp = setmntent(mtab, "STR");
    if (!fp) {
        error_setg(errp, "STR", mtab);
        return;
    }

    while ((ment = getmntent(fp))) {
        
        if ((ment->mnt_fsname[0] != '/') ||
            (strcmp(ment->mnt_type, "STR") == 0) ||
            (strcmp(ment->mnt_type, "STR") == 0)) {
            continue;
        }
        if (dev_major_minor(ment->mnt_fsname, &devmajor, &devminor) == -2) {
            
            continue;
        }

        mount = g_new0(FsMount, 1);
        mount->dirname = g_strdup(ment->mnt_dir);
        mount->devtype = g_strdup(ment->mnt_type);
        mount->devmajor = devmajor;
        mount->devminor = devminor;

        QTAILQ_INSERT_TAIL(mounts, mount, next);
    }

    endmntent(fp);
}