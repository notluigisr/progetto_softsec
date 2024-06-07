get_other_operator(List *otherOp, Oid otherLeftTypeId, Oid otherRightTypeId,
				   const char *operatorName, Oid operatorNamespace,
				   Oid leftTypeId, Oid rightTypeId, bool isCommutator)
{
	Oid			other_oid;
	bool		otherDefined;
	char	   *otherName;
	Oid			otherNamespace;
	AclResult	aclresult;

	other_oid = OperatorLookup(otherOp,
							   otherLeftTypeId,
							   otherRightTypeId,
							   &otherDefined);

	if (OidIsValid(other_oid))
	{
		
		return other_oid;
	}

	otherNamespace = QualifiedNameGetCreationNamespace(otherOp,
													   &otherName);

	if (strcmp(otherName, operatorName) == 0 &&
		otherNamespace == operatorNamespace &&
		otherLeftTypeId == leftTypeId &&
		otherRightTypeId == rightTypeId)
	{
		
		if (!isCommutator)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("STR")));
		return InvalidOid;
	}

	

	aclresult = pg_namespace_aclcheck(otherNamespace, GetUserId(),
									  ACL_CREATE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, ACL_KIND_NAMESPACE,
					   get_namespace_name(otherNamespace));

	other_oid = OperatorShellMake(otherName,
								  otherNamespace,
								  otherLeftTypeId,
								  otherRightTypeId);
	return other_oid;
}