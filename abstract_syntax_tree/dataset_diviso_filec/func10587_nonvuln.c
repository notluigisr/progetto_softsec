cmsUInt32Number CMSEXPORT cmsGetProfileInfo(cmsHPROFILE hProfile, cmsInfoType Info,
                                            const char LanguageCode[3], const char CountryCode[3],
                                            wchar_t* Buffer, cmsUInt32Number BufferSize)
{
    const cmsMLU* mlu = GetInfo(hProfile, Info);
    if (mlu == NULL) return 0;

    return cmsMLUgetWide(mlu, LanguageCode, CountryCode, Buffer, BufferSize);
}