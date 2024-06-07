PipelineD::buildInnerQueryExecutor(const CollectionPtr& collection,
                                   const NamespaceString& nss,
                                   const AggregateCommandRequest* aggRequest,
                                   Pipeline* pipeline) {
    auto expCtx = pipeline->getContext();

    
    Pipeline::SourceContainer& sources = pipeline->_sources;

    if (!sources.empty() && !sources.front()->constraints().requiresInputDocSource) {
        return {};
    }

    if (!sources.empty()) {
        
        
        auto&& [sampleStage, unpackBucketStage] = extractSampleUnpackBucket(sources);

        
        if (collection && sampleStage) {
            auto [attachExecutorCallback, exec] =
                buildInnerQueryExecutorSample(sampleStage, unpackBucketStage, collection, pipeline);
            if (exec) {
                return std::make_pair(std::move(attachExecutorCallback), std::move(exec));
            }
        }
    }

    
    
    const auto geoNearStage =
        sources.empty() ? nullptr : dynamic_cast<DocumentSourceGeoNear*>(sources.front().get());
    if (geoNearStage) {
        return buildInnerQueryExecutorGeoNear(collection, nss, aggRequest, pipeline);
    } else {
        return buildInnerQueryExecutorGeneric(collection, nss, aggRequest, pipeline);
    }
}