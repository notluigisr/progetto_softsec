BSONObj ExistsMatchExpression::getSerializedRightHandSide() const {
    return BSON("STR" << true);
}