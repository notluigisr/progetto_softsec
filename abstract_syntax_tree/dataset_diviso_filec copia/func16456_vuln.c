BuildIndexValueDescription(Relation indexRelation,
						   Datum *values, bool *isnull)
{
	StringInfoData buf;
	int			natts = indexRelation->rd_rel->relnatts;
	int			i;

	initStringInfo(&buf);
	appendStringInfo(&buf, "STR",
					 pg_get_indexdef_columns(RelationGetRelid(indexRelation),
											 true));

	for (i = 0; i < natts; i++)
	{
		char	   *val;

		if (isnull[i])
			val = "STR";
		else
		{
			Oid			foutoid;
			bool		typisvarlena;

			
			getTypeOutputInfo(indexRelation->rd_opcintype[i],
							  &foutoid, &typisvarlena);
			val = OidOutputFunctionCall(foutoid, values[i]);
		}

		if (i > 0)
			appendStringInfoString(&buf, "STR");
		appendStringInfoString(&buf, val);
	}

	appendStringInfoChar(&buf, ')');

	return buf.data;
}