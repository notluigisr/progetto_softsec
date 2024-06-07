void InMatchExpression::debugString(StringBuilder& debug, int indentationLevel) const {
    _debugAddSpace(debug, indentationLevel);
    debug << path() << "STR";
    debug << "STR";
    for (auto&& equality : _equalitySet) {
        debug << equality.toString(false) << "STR";
    }
    for (auto&& regex : _regexes) {
        regex->shortDebugString(debug);
        debug << "STR";
    }
    debug << "STR";
    MatchExpression::TagData* td = getTag();
    if (nullptr != td) {
        debug << "STR";
        td->debugString(&debug);
    }
    debug << "STR";
}