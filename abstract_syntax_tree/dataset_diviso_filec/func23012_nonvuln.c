static void exif_tag_ht_dtor(zval *zv)
{
	HashTable *ht = Z_PTR_P(zv);
	zend_hash_destroy(ht);
	free(ht);
}