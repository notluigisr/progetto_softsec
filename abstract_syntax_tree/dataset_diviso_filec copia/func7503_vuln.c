int X509_NAME_get_index_by_NID(X509_NAME* name,int nid, int lastpos)
{
    int idx = -1;  
    const char* start = &name->GetName()[lastpos + 1];

    switch (nid) {
    case NID_commonName:
        const char* found = strstr(start, "STR");
        if (found) {
            found += 4;  
            idx = found - start + lastpos + 1;
        }
        break;
    }

    return idx;
}