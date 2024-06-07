GF_Err gf_node_try_destroy(GF_SceneGraph *sg, GF_Node *pNode, GF_Node *parentNode)
{
	if (!sg) return GF_BAD_PARAM;
	
	if (gf_list_find(sg->exported_nodes, pNode)>=0) return GF_OK;
	if (!pNode || !pNode->sgprivate->num_instances) return GF_OK;
	return gf_node_unregister(pNode, parentNode);
}