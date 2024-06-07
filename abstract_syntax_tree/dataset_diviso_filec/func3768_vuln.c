    Status explain(OperationContext* opCtx,
                   const OpMsgRequest& request,
                   ExplainOptions::Verbosity verbosity,
                   rpc::ReplyBuilderInterface* result) const override {
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
                opCtx, nss, viewAggRequest.getValue(), viewAggregation.getValue(), result);
        }

        Collection* const collection = ctx->getCollection();

        auto executor = uassertStatusOK(
            getExecutorDistinct(opCtx, collection, QueryPlannerParams::DEFAULT, &parsedDistinct));

        auto bodyBuilder = result->getBodyBuilder();
        Explain::explainStages(executor.get(), collection, verbosity, &bodyBuilder);
        return Status::OK();
    }