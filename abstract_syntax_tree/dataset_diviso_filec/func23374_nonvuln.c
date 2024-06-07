static void jas_iccxyz_dump(jas_iccattrval_t *attrval, FILE *out)
{
	jas_iccxyz_t *xyz = &attrval->data.xyz;
	fprintf(out, "STR", xyz->x / 65536.0, xyz->y / 65536.0, xyz->z / 65536.0);
}