void CLua::save_persist()
{
    string persist;
    
    
    execfile("STR", true, true);
    callfn("STR", &persist);
    if (Options.no_save)
        return;

    FILE *f;
    const string persistfile = _get_persist_file();

    
    if (persist.empty() && !file_exists(persistfile))
        return;

    f = fopen_u(persistfile.c_str(), "STR");
    if (!f)
    {
        mprf(MSGCH_ERROR, "STR", persistfile.c_str());
        return;
    }

    fprintf(f, "STR"
               "STR"
            "STR",
            OUTS(CRAWL), 
            OUTS(Version::Long)); 
    fprintf(f, "STR", persist.c_str());
    fclose(f);
}