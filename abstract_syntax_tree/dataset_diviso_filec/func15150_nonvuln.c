static void GTextFieldAddHSb(GTextField *gt) {
    GGadgetData gd;

    memset(&gd,'\0',sizeof(gd));
    gd.pos.x = gt->g.r.x; gd.pos.width = gt->g.r.width;
    gd.pos.height = GDrawPointsToPixels(gt->g.base,_GScrollBar_Width);
    gd.pos.y = gt->g.r.y+gt->g.r.height - gd.pos.height;
    gd.flags = (gt->g.state==gs_invisible?0:gg_visible)|gg_enabled|gg_pos_in_pixels;
    gd.handle_controlevent = gtextfield_hscroll;
    gt->hsb = (GScrollBar *) GScrollBarCreate(gt->g.base,&gd,gt);
    gt->hsb->g.contained = true;

    gd.pos.height += GDrawPointsToPixels(gt->g.base,1);
    gt->g.r.height -= gd.pos.height;
    gt->g.inner.height -= gd.pos.height;
    if ( gt->vsb!=NULL ) {
	gt->vsb->g.r.height -= gd.pos.height;
	gt->vsb->g.inner.height -= gd.pos.height;
    }
}