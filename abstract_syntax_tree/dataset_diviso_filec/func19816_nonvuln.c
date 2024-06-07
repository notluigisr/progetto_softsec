Value ExpressionReplaceBase::serialize(bool explain) const {
    return Value(Document{{getOpName(),
                           Document{{"STR", _input->serialize(explain)},
                                    {"STR", _find->serialize(explain)},
                                    {"STR", _replacement->serialize(explain)}}}});
}