void CTXLoad_NodeCallback(void *cbk, GF_SGNodeCbkType type, GF_Node *node, void *param)
{
	if ((type==GF_SG_CALLBACK_INIT) && (gf_node_get_tag(node) == TAG_MPEG4_Conditional) ) {
		M_Conditional*c = (M_Conditional*)node;
		c->on_activate = CTXLoad_OnActivate;
		c->on_reverseActivate = CTXLoad_OnReverseActivate;
		gf_node_set_private(node, cbk);
	} else {
		gf_scene_node_callback(cbk, type, node, param);
	}
}