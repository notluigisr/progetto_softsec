cmsBool CMSEXPORT cmsIT8SetPropertyHex(cmsHANDLE hIT8, const char* cProp, cmsUInt32Number Val)
{
    cmsIT8* it8 = (cmsIT8*) hIT8;
    char Buffer[1024];

    sprintf(Buffer, "STR", Val);

    return AddToList(it8, &GetTable(it8)->HeaderList, cProp, NULL, Buffer, WRITE_HEXADECIMAL) != NULL;
}