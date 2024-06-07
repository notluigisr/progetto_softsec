ClientRequestContext::clientStoreIdStart()
{
    debugs(33, 5,"STR");

    if (Config.accessList.store_id) {
        acl_checklist = clientAclChecklistCreate(Config.accessList.store_id, http);
        acl_checklist->nonBlockingCheck(clientStoreIdAccessCheckDone, this);
    } else
        storeIdStart(http, clientStoreIdDoneWrapper, this);
}