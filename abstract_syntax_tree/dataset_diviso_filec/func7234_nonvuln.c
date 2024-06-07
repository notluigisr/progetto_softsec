void ExpressionConvert::_doAddDependencies(DepsTracker* deps) const {
    _input->addDependencies(deps);
    _to->addDependencies(deps);
    if (_onError) {
        _onError->addDependencies(deps);
    }
    if (_onNull) {
        _onNull->addDependencies(deps);
    }
}