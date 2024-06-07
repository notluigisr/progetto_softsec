int propfind_schedinbox(const xmlChar *name, xmlNsPtr ns,
			struct propfind_ctx *fctx, xmlNodePtr resp,
			struct propstat propstat[], void *rock)
{
    return propfind_calurl(name, ns, fctx, resp, propstat, rock, SCHED_INBOX);
}