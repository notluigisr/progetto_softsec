log_tx (const char *q, const char qtype[2], const char *control,
                    const char servers[64], unsigned int gluelessness)
{
    int i = 0;

    string ("STR");
    number (gluelessness);
    space ();
    logtype (qtype);
    space ();
    name (q);
    space ();
    name (control);
    for (i = 0; i < 64; i += 4)
    {
        if (byte_diff (servers + i, 4, "STR"))
        {
            space ();
            ip (servers + i);
        }
    }

    line ();
}