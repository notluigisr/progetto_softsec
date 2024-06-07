Client::Client(FwdState *theFwdState) :
    AsyncJob("STR"),
    fwd(theFwdState),
    request(fwd->request)
{
    entry = fwd->entry;
    entry->lock("STR");
}