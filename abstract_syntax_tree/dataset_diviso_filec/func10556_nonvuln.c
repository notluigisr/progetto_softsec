GF_SceneGraph *gf_node_get_graph(GF_Node *node)
{
	return (node ? node->sgprivate->scenegraph : NULL);
}