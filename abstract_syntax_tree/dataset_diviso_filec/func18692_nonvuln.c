projection_ast::Projection createProjection(const char* queryStr, const char* projStr) {
    BSONObj query = fromjson(queryStr);
    BSONObj projObj = fromjson(projStr);
    return createProjection(query, projObj);
}