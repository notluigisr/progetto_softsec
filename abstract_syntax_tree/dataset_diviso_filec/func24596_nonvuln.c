qemuProcessHandleDeviceDeleted(qemuMonitorPtr mon G_GNUC_UNUSED,
                               virDomainObjPtr vm,
                               const char *devAlias,
                               void *opaque)
{
    virQEMUDriverPtr driver = opaque;
    struct qemuProcessEvent *processEvent = NULL;
    char *data;

    virObjectLock(vm);

    VIR_DEBUG("STR",
              devAlias, vm, vm->def->name);

    if (qemuDomainSignalDeviceRemoval(vm, devAlias,
                                      QEMU_DOMAIN_UNPLUGGING_DEVICE_STATUS_OK))
        goto cleanup;

    processEvent = g_new0(struct qemuProcessEvent, 1);

    processEvent->eventType = QEMU_PROCESS_EVENT_DEVICE_DELETED;
    data = g_strdup(devAlias);
    processEvent->data = data;
    processEvent->vm = virObjectRef(vm);

    if (virThreadPoolSendJob(driver->workerPool, 0, processEvent) < 0) {
        virObjectUnref(vm);
        goto error;
    }

 cleanup:
    virObjectUnlock(vm);
    return 0;
 error:
    qemuProcessEventFree(processEvent);
    goto cleanup;
}