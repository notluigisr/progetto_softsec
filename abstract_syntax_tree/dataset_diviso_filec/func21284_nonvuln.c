_equalValue(const Value *a, const Value *b)
{
	COMPARE_SCALAR_FIELD(type);

	switch (a->type)
	{
		case T_Integer:
			COMPARE_SCALAR_FIELD(val.ival);
			break;
		case T_Float:
		case T_String:
		case T_BitString:
			COMPARE_STRING_FIELD(val.str);
			break;
		case T_Null:
			
			break;
		default:
			elog(ERROR, "STR", (int) a->type);
			break;
	}

	return true;
}