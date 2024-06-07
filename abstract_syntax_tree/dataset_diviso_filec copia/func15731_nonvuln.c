frame_add_height(frame_T *frp, int n)
{
    frame_new_height(frp, frp->fr_height + n, FALSE, FALSE);
    for (;;)
    {
	frp = frp->fr_parent;
	if (frp == NULL)
	    break;
	frp->fr_height += n;
    }
}