rsvg_term (void)
{
#ifdef HAVE_GSF
    gsf_shutdown ();
#endif

    xmlCleanupParser ();
}