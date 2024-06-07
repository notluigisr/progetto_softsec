gql_root_type() {
    if (NULL == _gql_root_type && NULL != gql_type_func) {
	_gql_root_type = gql_type_func(gql_root);
    }
    return _gql_root_type;
}