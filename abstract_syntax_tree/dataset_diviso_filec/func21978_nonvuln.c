void DocumentSourceLookUp::resolveLetVariables(const Document& localDoc, Variables* variables) {
    invariant(variables);

    for (auto& letVar : _letVariables) {
        auto value = letVar.expression->evaluate(localDoc, &pExpCtx->variables);
        variables->setConstantValue(letVar.id, value);
    }
}