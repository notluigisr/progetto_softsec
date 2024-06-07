void AuthorizationManager::logOp(
    OperationContext* txn, const char* op, const char* ns, const BSONObj& o, const BSONObj* o2) {
    if (appliesToAuthzData(op, ns, o)) {
        _externalState->logOp(txn, op, ns, o, o2);
        _invalidateRelevantCacheData(op, ns, o, o2);
    }
}