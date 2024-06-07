static int doCreateImage(struct nc_state_t *nc, ncMetadata * pMeta, char *instanceId, char *volumeId, char *remoteDev)
{
    
    if (instanceId == NULL || remoteDev == NULL || volumeId == NULL) {
        LOGERROR("STR" : volumeId));
        return EUCA_ERROR;
    }
    
    ncInstance *instance = find_instance(&global_instances, instanceId);
    if (instance == NULL) {
        LOGERROR("STR", instanceId, volumeId);
        return EUCA_NOT_FOUND_ERROR;
    }
    
    struct createImage_params_t *params = EUCA_ZALLOC(1, sizeof(struct createImage_params_t));
    if (params == NULL)
        return cleanup_createImage_task(instance, params, NO_STATE, CREATEIMAGE_FAILED);

    params->instance = instance;       
    params->volumeId = strdup(volumeId);
    params->remoteDev = strdup(remoteDev);

    
    sem_p(inst_sem);
    instance->createImageTime = time(NULL);
    change_state(instance, CREATEIMAGE_SHUTDOWN);
    change_createImage_state(instance, CREATEIMAGE_IN_PROGRESS);
    sem_v(inst_sem);

    int err = find_and_terminate_instance(instanceId);
    if (err != EUCA_OK) {
        EUCA_FREE(params);
        return err;
    }

    sem_p(inst_sem);
    copy_instances();
    sem_v(inst_sem);

    
    pthread_attr_t tattr;
    pthread_t tid;
    pthread_attr_init(&tattr);
    pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
    if (pthread_create(&tid, &tattr, createImage_thread, (void *)params) != 0) {
        LOGERROR("STR", instanceId, volumeId);
        return cleanup_createImage_task(instance, params, SHUTOFF, CREATEIMAGE_FAILED);
    }

    return EUCA_OK;
}