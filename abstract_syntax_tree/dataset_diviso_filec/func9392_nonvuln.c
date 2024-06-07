DepsTracker::State DocumentSourceGroup::getDependencies(DepsTracker* deps) const {
    
    for (size_t i = 0; i < _idExpressions.size(); i++) {
        _idExpressions[i]->addDependencies(deps);
    }

    
    for (auto&& accumulatedField : _accumulatedFields) {
        accumulatedField.expr.argument->addDependencies(deps);
        
    }

    return DepsTracker::State::EXHAUSTIVE_ALL;
}