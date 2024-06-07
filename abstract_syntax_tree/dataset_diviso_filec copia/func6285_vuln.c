virSecuritySELinuxMCSFind(virSecurityManager *mgr,
                          const char *sens,
                          int catMin,
                          int catMax)
{
    virSecuritySELinuxData *data = virSecurityManagerGetPrivateData(mgr);
    int catRange;
    char *mcs = NULL;

    
    catRange = (catMax - catMin) + 1;

    if (catRange < 8) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("STR"),
                       catMin, catMax);
        return NULL;
    }

    VIR_DEBUG("STR",
              sens, catMin, catMax, catRange);

    for (;;) {
        int c1 = virRandomInt(catRange);
        int c2 = virRandomInt(catRange);

        VIR_DEBUG("STR", sens, c1 + catMin, c2 + catMin);

        if (c1 == c2) {
            mcs = g_strdup_printf("STR", sens, catMin + c1);
        } else {
            if (c1 > c2) {
                int t = c1;
                c1 = c2;
                c2 = t;
            }
            mcs = g_strdup_printf("STR", sens, catMin + c1, catMin + c2);
        }

        if (virHashLookup(data->mcs, mcs) == NULL)
            break;

        VIR_FREE(mcs);
    }

    return mcs;
}