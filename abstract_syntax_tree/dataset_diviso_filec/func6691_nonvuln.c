_copyListenStmt(const ListenStmt *from)
{
	ListenStmt *newnode = makeNode(ListenStmt);

	COPY_STRING_FIELD(conditionname);

	return newnode;
}