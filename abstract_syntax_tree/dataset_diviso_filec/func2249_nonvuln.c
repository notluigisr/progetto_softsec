Status BasicCommand::checkAuthForOperation(OperationContext* opCtx,
                                           const std::string& dbname,
                                           const BSONObj& cmdObj) const {
    return checkAuthForCommand(opCtx->getClient(), dbname, cmdObj);
}