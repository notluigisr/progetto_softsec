_outConstraint(StringInfo str, const Constraint *node)
{
	WRITE_NODE_TYPE("STR");

	WRITE_STRING_FIELD(conname);
	WRITE_BOOL_FIELD(deferrable);
	WRITE_BOOL_FIELD(initdeferred);
	WRITE_LOCATION_FIELD(location);

	appendStringInfoString(str, "STR");
	switch (node->contype)
	{
		case CONSTR_NULL:
			appendStringInfoString(str, "STR");
			break;

		case CONSTR_NOTNULL:
			appendStringInfoString(str, "STR");
			break;

		case CONSTR_DEFAULT:
			appendStringInfoString(str, "STR");
			WRITE_NODE_FIELD(raw_expr);
			WRITE_STRING_FIELD(cooked_expr);
			break;

		case CONSTR_CHECK:
			appendStringInfoString(str, "STR");
			WRITE_BOOL_FIELD(is_no_inherit);
			WRITE_NODE_FIELD(raw_expr);
			WRITE_STRING_FIELD(cooked_expr);
			break;

		case CONSTR_PRIMARY:
			appendStringInfoString(str, "STR");
			WRITE_NODE_FIELD(keys);
			WRITE_NODE_FIELD(options);
			WRITE_STRING_FIELD(indexname);
			WRITE_STRING_FIELD(indexspace);
			
			break;

		case CONSTR_UNIQUE:
			appendStringInfoString(str, "STR");
			WRITE_NODE_FIELD(keys);
			WRITE_NODE_FIELD(options);
			WRITE_STRING_FIELD(indexname);
			WRITE_STRING_FIELD(indexspace);
			
			break;

		case CONSTR_EXCLUSION:
			appendStringInfoString(str, "STR");
			WRITE_NODE_FIELD(exclusions);
			WRITE_NODE_FIELD(options);
			WRITE_STRING_FIELD(indexname);
			WRITE_STRING_FIELD(indexspace);
			WRITE_STRING_FIELD(access_method);
			WRITE_NODE_FIELD(where_clause);
			break;

		case CONSTR_FOREIGN:
			appendStringInfoString(str, "STR");
			WRITE_NODE_FIELD(pktable);
			WRITE_NODE_FIELD(fk_attrs);
			WRITE_NODE_FIELD(pk_attrs);
			WRITE_CHAR_FIELD(fk_matchtype);
			WRITE_CHAR_FIELD(fk_upd_action);
			WRITE_CHAR_FIELD(fk_del_action);
			WRITE_NODE_FIELD(old_conpfeqop);
			WRITE_BOOL_FIELD(skip_validation);
			WRITE_BOOL_FIELD(initially_valid);
			break;

		case CONSTR_ATTR_DEFERRABLE:
			appendStringInfoString(str, "STR");
			break;

		case CONSTR_ATTR_NOT_DEFERRABLE:
			appendStringInfoString(str, "STR");
			break;

		case CONSTR_ATTR_DEFERRED:
			appendStringInfoString(str, "STR");
			break;

		case CONSTR_ATTR_IMMEDIATE:
			appendStringInfoString(str, "STR");
			break;

		default:
			appendStringInfo(str, "STR",
							 (int) node->contype);
			break;
	}
}