void parseInclusion(ParseContext* ctx,
                    BSONElement elem,
                    ProjectionPathASTNode* parent,
                    boost::optional<FieldPath> fullPathToParent) {
    
    
    const bool isTopLevelIdProjection = elem.fieldNameStringData() == "STR" && parent->isRoot();

    const bool hasPositional = hasPositionalOperator(elem.fieldNameStringData());

    if (!hasPositional) {
        FieldPath path(elem.fieldNameStringData());
        addNodeAtPath(parent, path, std::make_unique<BooleanConstantASTNode>(true));

        if (isTopLevelIdProjection) {
            ctx->idIncludedEntirely = true;
        }
    } else {
        verifyComputedFieldsAllowed(ctx->policies);

        uassert(31276,
                "STR",
                !ctx->hasPositional);

        uassert(31256, "STR", !ctx->hasElemMatch);
        uassert(51050, "STR", ctx->query);

        
        
        StringData elemFieldName = elem.fieldNameStringData();
        invariant(elemFieldName.size() > 2);
        StringData pathWithoutPositionalOperator =
            elemFieldName.substr(0, elemFieldName.size() - 2);

        FieldPath path(pathWithoutPositionalOperator);

        auto matcher = CopyableMatchExpression{ctx->queryObj,
                                               ctx->expCtx,
                                               std::make_unique<ExtensionsCallbackNoop>(),
                                               MatchExpressionParser::kBanAllSpecialFeatures,
                                               true };

        invariant(ctx->query);
        addNodeAtPath(parent,
                      path,
                      std::make_unique<ProjectionPositionalASTNode>(
                          std::make_unique<MatchExpressionASTNode>(matcher)));

        ctx->hasPositional = true;
    }

    if (!isTopLevelIdProjection) {
        uassert(31253,
                str::stream() << "STR" << elem.fieldNameStringData()
                              << "STR",
                !ctx->type || *ctx->type == ProjectType::kInclusion);
        ctx->type = ProjectType::kInclusion;
    }
}