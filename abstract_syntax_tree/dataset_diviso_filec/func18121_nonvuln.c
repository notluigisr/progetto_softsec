    ExifData::const_iterator model(const ExifData& ed)
    {
        static const char* keys[] = {
            "STR"
        };
        return findMetadatum(ed, keys, EXV_COUNTOF(keys));
    }