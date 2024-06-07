
static int
xmlXPathIsPositionalPredicate(xmlXPathParserContextPtr ctxt,
			    xmlXPathStepOpPtr op,
			    int *maxPos)
{

    xmlXPathStepOpPtr exprOp;

    

    
    if ((op->op != XPATH_OP_PREDICATE) && (op->op != XPATH_OP_FILTER))
	return(0);

    if (op->ch2 != -1) {
	exprOp = &ctxt->comp->steps[op->ch2];
    } else
	return(0);

    if ((exprOp != NULL) &&
	(exprOp->op == XPATH_OP_VALUE) &&
	(exprOp->value4 != NULL) &&
	(((xmlXPathObjectPtr) exprOp->value4)->type == XPATH_NUMBER))
    {
        double floatval = ((xmlXPathObjectPtr) exprOp->value4)->floatval;

	

        if ((floatval > INT_MIN) && (floatval < INT_MAX)) {
	    *maxPos = (int) floatval;
            if (floatval == (double) *maxPos)
                return(1);
        }
    }