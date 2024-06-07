    Status explain(OperationContext* opCtx,
                   const OpMsgRequest& opMsgRequest,
                   ExplainOptions::Verbosity verbosity,
                   BSONObjBuilder* out) const override {
        std::string dbname = opMsgRequest.getDatabase().toString();
        const BSONObj& cmdObj = opMsgRequest.body;
        
        
        boost::optional<AutoGetCollectionForReadCommand> ctx;
        ctx.emplace(opCtx,
                    CommandHelpers::parseNsOrUUID(dbname, cmdObj),
                    AutoGetCollection::ViewMode::kViewsPermitted);
        const auto nss = ctx->getNss();

        const bool isExplain = true;
        auto request = CountRequest::parseFromBSON(nss, cmdObj, isExplain);
        if (!request.isOK()) {
            return request.getStatus();
        }

        if (ctx->getView()) {
            
            ctx.reset();

            auto viewAggregation = request.getValue().asAggregationCommand();
            if (!viewAggregation.isOK()) {
                return viewAggregation.getStatus();
            }

            auto viewAggRequest = AggregationRequest::parseFromBSON(
                request.getValue().getNs(), viewAggregation.getValue(), verbosity);
            if (!viewAggRequest.isOK()) {
                return viewAggRequest.getStatus();
            }

            return runAggregate(opCtx,
                                viewAggRequest.getValue().getNamespaceString(),
                                viewAggRequest.getValue(),
                                viewAggregation.getValue(),
                                *out);
        }

        Collection* const collection = ctx->getCollection();

        
        
        auto rangePreserver = CollectionShardingState::get(opCtx, nss)->getMetadata(opCtx);

        auto statusWithPlanExecutor =
            getExecutorCount(opCtx, collection, request.getValue(), true );
        if (!statusWithPlanExecutor.isOK()) {
            return statusWithPlanExecutor.getStatus();
        }

        auto exec = std::move(statusWithPlanExecutor.getValue());

        Explain::explainStages(exec.get(), collection, verbosity, out);
        return Status::OK();
    }