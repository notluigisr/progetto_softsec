virDomainSoundDefCheckABIStability(virDomainSoundDefPtr src,
                                   virDomainSoundDefPtr dst)
{
    if (src->model != dst->model) {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                       _("STR"),
                       virDomainSoundModelTypeToString(dst->model),
                       virDomainSoundModelTypeToString(src->model));
        return false;
    }

    if (!virDomainDeviceInfoCheckABIStability(&src->info, &dst->info))
        return false;

    return true;
}