_copyBitmapOr(const BitmapOr *from)
{
	BitmapOr   *newnode = makeNode(BitmapOr);

	
	CopyPlanFields((const Plan *) from, (Plan *) newnode);

	
	COPY_NODE_FIELD(bitmapplans);

	return newnode;
}