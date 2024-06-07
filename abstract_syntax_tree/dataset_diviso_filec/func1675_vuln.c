DocumentSource::GetNextResult DocumentSourceUnionWith::doGetNext() {
    if (!_pipeline) {
        
        return GetNextResult::makeEOF();
    }

    if (_executionState == ExecutionProgress::kIteratingSource) {
        auto nextInput = pSource->getNext();
        if (!nextInput.isEOF()) {
            return nextInput;
        }
        _executionState = ExecutionProgress::kStartingSubPipeline;
        
        
    }

    if (_executionState == ExecutionProgress::kStartingSubPipeline) {
        auto serializedPipe = _pipeline->serializeToBson();
        LOGV2_DEBUG(23869,
                    1,
                    "STR",
                    "STR"_attr = serializedPipe);
        
        
        if (pExpCtx->variables.hasConstantValue(Variables::kSearchMetaId)) {
            _pipeline->getContext()->variables.setReservedValue(
                Variables::kSearchMetaId,
                pExpCtx->variables.getValue(Variables::kSearchMetaId, Document()),
                true);
        }
        try {
            _pipeline =
                pExpCtx->mongoProcessInterface->attachCursorSourceToPipeline(_pipeline.release());
            _executionState = ExecutionProgress::kIteratingSubPipeline;
        } catch (const ExceptionFor<ErrorCodes::CommandOnShardedViewNotSupportedOnMongod>& e) {
            _pipeline = buildPipelineFromViewDefinition(
                pExpCtx,
                ExpressionContext::ResolvedNamespace{e->getNamespace(), e->getPipeline()},
                serializedPipe);
            LOGV2_DEBUG(4556300,
                        3,
                        "STR"
                        "STR",
                        "STR"_attr = e->getNamespace(),
                        "STR"_attr = Value(e->getPipeline()),
                        "STR"_attr = _pipeline->serializeToBson());
            return doGetNext();
        }
    }

    auto res = _pipeline->getNext();
    if (res)
        return std::move(*res);

    
    recordPlanSummaryStats(*_pipeline);

    _executionState = ExecutionProgress::kFinished;
    return GetNextResult::makeEOF();
}