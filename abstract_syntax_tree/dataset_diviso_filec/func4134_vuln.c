qemuProcessHandleMonitorEOF(qemuMonitorPtr mon,
                            virDomainObjPtr vm,
                            void *opaque)
{
    virQEMUDriverPtr driver = opaque;
    qemuDomainObjPrivatePtr priv;
    struct qemuProcessEvent *processEvent;

    virObjectLock(vm);

    VIR_DEBUG("STR", vm, vm->def->name);

    priv = vm->privateData;
    if (priv->beingDestroyed) {
        VIR_DEBUG("STR");
        goto cleanup;
    }

    processEvent = g_new0(struct qemuProcessEvent, 1);

    processEvent->eventType = QEMU_PROCESS_EVENT_MONITOR_EOF;
    processEvent->vm = virObjectRef(vm);

    if (virThreadPoolSendJob(driver->workerPool, 0, processEvent) < 0) {
        virObjectUnref(vm);
        qemuProcessEventFree(processEvent);
        goto cleanup;
    }

    
    qemuMonitorUnregister(mon);

    
    qemuDomainDestroyNamespace(driver, vm);

 cleanup:
    virObjectUnlock(vm);
}