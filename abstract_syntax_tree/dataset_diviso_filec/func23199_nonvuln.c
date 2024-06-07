void CommandHelpers::auditLogAuthEvent(OperationContext* opCtx,
                                       const CommandInvocation* invocation,
                                       const OpMsgRequest& request,
                                       ErrorCodes::Error err) {
    class Hook final : public audit::CommandInterface {
    public:
        explicit Hook(const CommandInvocation* invocation, const NamespaceString* nss)
            : _invocation(invocation), _nss(nss) {}

        void snipForLogging(mutablebson::Document* cmdObj) const override {
            if (_invocation) {
                _invocation->definition()->snipForLogging(cmdObj);
            }
        }

        StringData sensitiveFieldName() const override {
            if (_invocation) {
                return _invocation->definition()->sensitiveFieldName();
            }
            return StringData{};
        }

        StringData getName() const override {
            if (!_invocation) {
                return "STR"_sd;
            }
            return _invocation->definition()->getName();
        }

        NamespaceString ns() const override {
            return *_nss;
        }

        bool redactArgs() const override {
            return !_invocation;
        }

    private:
        const CommandInvocation* _invocation;
        const NamespaceString* _nss;
    };

    NamespaceString nss = invocation ? invocation->ns() : NamespaceString(request.getDatabase());
    audit::logCommandAuthzCheck(opCtx->getClient(), request, Hook(invocation, &nss), err);
}