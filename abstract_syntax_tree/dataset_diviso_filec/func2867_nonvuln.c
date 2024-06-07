intrusive_ptr<Expression> ExpressionDateToString::optimize() {
    _date = _date->optimize();
    if (_timeZone) {
        _timeZone = _timeZone->optimize();
    }

    if (ExpressionConstant::allNullOrConstant({_date, _timeZone})) {
        
        return ExpressionConstant::create(getExpressionContext(), evaluate(Document{}));
    }

    return this;
}