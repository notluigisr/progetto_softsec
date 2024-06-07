static int cleanup_bundling_task(ncInstance * instance, struct bundling_params_t *params, bundling_progress result)
{
    int rc = 0;
    char cmd[MAX_PATH] = { 0 };
    char buf[MAX_PATH] = { 0 };

    LOGINFO("STR", instance->instanceId, bundling_progress_names[result]);

    sem_p(inst_sem);
    {
        change_bundling_state(instance, result);
        copy_instances();
    }
    sem_v(inst_sem);

    if (params) {
        
        if ((result == BUNDLING_FAILED) || (result == BUNDLING_CANCELLED)) {
            if (!instance->bundleBucketExists) {
                snprintf(cmd, MAX_PATH, "STR", params->ncDeleteBundleCmd, params->bucketName, params->filePrefix);
            } else {
                snprintf(cmd, MAX_PATH, "STR", params->ncDeleteBundleCmd, params->bucketName, params->filePrefix);
                instance->bundleBucketExists = 0;
            }

            
            snprintf(buf, MAX_PATH, EUCALYPTUS_KEYS_DIR "STR", params->eucalyptusHomePath);
            setenv("STR", buf, 1);

            snprintf(buf, MAX_PATH, "STR");
            setenv("STR", buf, 1);

            snprintf(buf, MAX_PATH, EUCALYPTUS_KEYS_DIR "STR", params->eucalyptusHomePath);
            setenv("STR", buf, 1);

            snprintf(buf, MAX_PATH, "STR", params->walrusURL);
            setenv("STR", buf, 1);

            snprintf(buf, MAX_PATH, "STR", params->userPublicKey);
            setenv("STR", buf, 1);

            snprintf(buf, MAX_PATH, "STR");
            setenv("STR", buf, 1);

            snprintf(buf, MAX_PATH, EUCALYPTUS_KEYS_DIR "STR", params->eucalyptusHomePath);
            setenv("STR", buf, 1);

            snprintf(buf, MAX_PATH, EUCALYPTUS_KEYS_DIR "STR", params->eucalyptusHomePath);
            setenv("STR", buf, 1);

            LOGDEBUG("STR", cmd);
            rc = system(cmd);
            rc = rc >> 8;
            if (rc) {
                LOGWARN("STR", instance->instanceId, cmd, rc);
            }
        }

        EUCA_FREE(params->workPath);
        EUCA_FREE(params->bucketName);
        EUCA_FREE(params->filePrefix);
        EUCA_FREE(params->walrusURL);
        EUCA_FREE(params->userPublicKey);
        EUCA_FREE(params->diskPath);
        EUCA_FREE(params->eucalyptusHomePath);
        EUCA_FREE(params->ncBundleUploadCmd);
        EUCA_FREE(params->ncCheckBucketCmd);
        EUCA_FREE(params->ncDeleteBundleCmd);
        EUCA_FREE(params);
    }

    return ((result == BUNDLING_SUCCESS) ? EUCA_OK : EUCA_ERROR);
}