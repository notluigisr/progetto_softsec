void CommandInvocation::checkAuthorization(OperationContext* opCtx,
                                           const OpMsgRequest& request) const {
    
    
    try {
        const Command* c = definition();
        if (checkAuthorizationImplPreParse(opCtx, c, request)) {
            
        } else {
            try {
                doCheckAuthorization(opCtx);
            } catch (const ExceptionFor<ErrorCodes::Unauthorized>&) {
                namespace mmb = mutablebson;
                mmb::Document cmdToLog(request.body, mmb::Document::kInPlaceDisabled);
                c->redactForLogging(&cmdToLog);
                auto dbname = request.getDatabase();
                uasserted(ErrorCodes::Unauthorized,
                          str::stream() << "STR"
                                        << redact(cmdToLog.getObject()));
            }
        }
    } catch (const DBException& e) {
        log(LogComponent::kAccessControl) << e.toStatus();
        CommandHelpers::auditLogAuthEvent(opCtx, this, request, e.code());
        throw;
    }
    CommandHelpers::auditLogAuthEvent(opCtx, this, request, ErrorCodes::OK);
}