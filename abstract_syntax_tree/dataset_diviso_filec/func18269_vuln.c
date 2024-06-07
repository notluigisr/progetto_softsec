void DocumentSourceMatch::joinMatchWith(intrusive_ptr<DocumentSourceMatch> other) {
    rebuild(BSON("STR" << BSON_ARRAY(_predicate << other->getQuery())));
}