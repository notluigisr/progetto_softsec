GF_Err gf_dom_listener_del(GF_Node *listener, GF_DOMEventTarget *target)
{
	GF_FieldInfo info;
	if (!listener || !target) return GF_BAD_PARAM;
	if (gf_list_del_item(target->listeners, listener)<0) return GF_BAD_PARAM;

	if (gf_node_get_attribute_by_tag((GF_Node *)listener, TAG_XMLEV_ATT_event, GF_FALSE, GF_FALSE, &info) == GF_OK) {
		GF_EventType type = ((XMLEV_Event *)info.far_ptr)->type;
		gf_sg_unregister_event_type(listener->sgprivate->scenegraph, gf_dom_event_get_category(type));
	}
	listener->sgprivate->UserPrivate = NULL;

	gf_node_unregister((GF_Node *)listener, NULL);
	return GF_OK;
}