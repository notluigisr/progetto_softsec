    Status explain(OperationContext* opCtx,
                   const OpMsgRequest& request,
                   ExplainOptions::Verbosity verbosity,
                   BSONObjBuilder* out) const override {
        std::string dbname = request.getDatabase().toString();
        const BSONObj& cmdObj = request.body;
        
        
        boost::optional<AutoGetCollectionForReadCommand> ctx;
        ctx.emplace(opCtx,
                    CommandHelpers::parseNsOrUUID(dbname, cmdObj),
                    AutoGetCollection::ViewMode::kViewsPermitted);
        const auto nss = ctx->getNss();

        const ExtensionsCallbackReal extensionsCallback(opCtx, &nss);
        auto parsedDistinct =
            uassertStatusOK(ParsedDistinct::parse(opCtx, nss, cmdObj, extensionsCallback, true));

        if (ctx->getView()) {
            
            ctx.reset();

            auto viewAggregation = parsedDistinct.asAggregationCommand();
            if (!viewAggregation.isOK()) {
                return viewAggregation.getStatus();
            }

            auto viewAggRequest =
                AggregationRequest::parseFromBSON(nss, viewAggregation.getValue(), verbosity);
            if (!viewAggRequest.isOK()) {
                return viewAggRequest.getStatus();
            }

            return runAggregate(
                opCtx, nss, viewAggRequest.getValue(), viewAggregation.getValue(), *out);
        }

        Collection* const collection = ctx->getCollection();

        auto executor =
            uassertStatusOK(getExecutorDistinct(opCtx, collection, nss.ns(), &parsedDistinct));

        Explain::explainStages(executor.get(), collection, verbosity, out);
        return Status::OK();
    }