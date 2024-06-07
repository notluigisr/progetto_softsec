DocumentSourceLookUp::DocumentSourceLookUp(NamespaceString fromNs,
                                           std::string as,
                                           const boost::intrusive_ptr<ExpressionContext>& expCtx)
    : DocumentSource(kStageName, expCtx),
      _fromNs(std::move(fromNs)),
      _as(std::move(as)),
      _variables(expCtx->variables),
      _variablesParseState(expCtx->variablesParseState.copyWith(_variables.useIdGenerator())) {
    const auto& resolvedNamespace = expCtx->getResolvedNamespace(_fromNs);
    _resolvedNs = resolvedNamespace.ns;
    _resolvedPipeline = resolvedNamespace.pipeline;
    _fromExpCtx = expCtx->copyWith(_resolvedNs);

    _fromExpCtx->subPipelineDepth += 1;
    uassert(ErrorCodes::MaxSubPipelineDepthExceeded,
            str::stream() << "STR"
                          << kMaxSubPipelineDepth,
            _fromExpCtx->subPipelineDepth <= kMaxSubPipelineDepth);
}