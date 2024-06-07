        void explain(OperationContext* opCtx,
                     ExplainOptions::Verbosity verbosity,
                     rpc::ReplyBuilderInterface* result) override {
            
            
            boost::optional<AutoGetCollectionForReadCommand> ctx;
            ctx.emplace(opCtx,
                        CommandHelpers::parseNsOrUUID(_dbName, _request.body),
                        AutoGetCollection::ViewMode::kViewsPermitted);
            const auto nss = ctx->getNss();

            
            const bool isExplain = true;
            auto qr =
                uassertStatusOK(QueryRequest::makeFromFindCommand(nss, _request.body, isExplain));

            
            const ExtensionsCallbackReal extensionsCallback(opCtx, &nss);
            const boost::intrusive_ptr<ExpressionContext> expCtx;
            auto cq = uassertStatusOK(
                CanonicalQuery::canonicalize(opCtx,
                                             std::move(qr),
                                             expCtx,
                                             extensionsCallback,
                                             MatchExpressionParser::kAllowAllSpecialFeatures));

            if (ctx->getView()) {
                
                ctx.reset();

                
                
                const auto& qr = cq->getQueryRequest();
                auto viewAggregationCommand = uassertStatusOK(qr.asAggregationCommand());

                
                
                auto aggRequest = uassertStatusOK(
                    AggregationRequest::parseFromBSON(nss, viewAggregationCommand, verbosity));

                try {
                    uassertStatusOK(
                        runAggregate(opCtx, nss, aggRequest, viewAggregationCommand, result));
                } catch (DBException& error) {
                    if (error.code() == ErrorCodes::InvalidPipelineOperator) {
                        uasserted(ErrorCodes::InvalidPipelineOperator,
                                  str::stream() << "STR"
                                                << error.what());
                    }
                    throw;
                }
                return;
            }

            
            
            Collection* const collection = ctx->getCollection();

            
            auto exec = uassertStatusOK(getExecutorFind(opCtx, collection, nss, std::move(cq)));

            auto bodyBuilder = result->getBodyBuilder();
            
            Explain::explainStages(exec.get(), collection, verbosity, &bodyBuilder);
        }