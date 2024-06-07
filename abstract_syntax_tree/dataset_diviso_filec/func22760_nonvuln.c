virDomainResctrlMonDefFree(virDomainResctrlMonDefPtr domresmon)
{
    if (!domresmon)
        return;

    virBitmapFree(domresmon->vcpus);
    virObjectUnref(domresmon->instance);
    VIR_FREE(domresmon);
}