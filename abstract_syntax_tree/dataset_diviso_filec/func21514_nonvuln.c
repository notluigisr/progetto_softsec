ClientRequestContext::checkNoCache()
{
    if (Config.accessList.noCache) {
        acl_checklist = clientAclChecklistCreate(Config.accessList.noCache, http);
        acl_checklist->nonBlockingCheck(checkNoCacheDoneWrapper, this);
    } else {
        
        checkNoCacheDone(ACCESS_ALLOWED);
    }
}