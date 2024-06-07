dwg_obj_is_subentity (const Dwg_Object *obj)
{
  const unsigned int type = obj->type;
  return (obj->supertype == DWG_SUPERTYPE_ENTITY)
         && (type == DWG_TYPE_ATTRIB || type == DWG_TYPE_VERTEX_2D
             || type == DWG_TYPE_VERTEX_3D || type == DWG_TYPE_VERTEX_MESH
             || type == DWG_TYPE_VERTEX_PFACE
             || type == DWG_TYPE_VERTEX_PFACE_FACE);
}