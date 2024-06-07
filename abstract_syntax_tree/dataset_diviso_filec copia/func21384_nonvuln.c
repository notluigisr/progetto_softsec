add_metadata_to_deploy_data (GVariantDict *metadata_dict,
                             GKeyFile     *keyfile)
{
  g_autofree char *application_runtime = NULL;
  g_autofree char *extension_of = NULL;

  application_runtime = g_key_file_get_string (keyfile,
                                               FLATPAK_METADATA_GROUP_APPLICATION,
                                               FLATPAK_METADATA_KEY_RUNTIME, NULL);
  extension_of = g_key_file_get_string (keyfile,
                                        FLATPAK_METADATA_GROUP_EXTENSION_OF,
                                        FLATPAK_METADATA_KEY_REF, NULL);

  if (application_runtime)
    g_variant_dict_insert_value (metadata_dict, "STR",
                                 g_variant_new_string (application_runtime));
  if (extension_of)
    g_variant_dict_insert_value (metadata_dict, "STR",
                                 g_variant_new_string (extension_of));
}