qemuProcessHandleJobStatusChange(qemuMonitorPtr mon G_GNUC_UNUSED,
                                 virDomainObjPtr vm,
                                 const char *jobname,
                                 int status,
                                 void *opaque)
{
    virQEMUDriverPtr driver = opaque;
    qemuDomainObjPrivatePtr priv;
    struct qemuProcessEvent *processEvent = NULL;
    qemuBlockJobDataPtr job = NULL;
    int jobnewstate;

    virObjectLock(vm);
    priv = vm->privateData;

    VIR_DEBUG("STR",
              jobname, vm, vm->def->name,
              qemuMonitorJobStatusTypeToString(status), status);

    if (!virQEMUCapsGet(priv->qemuCaps, QEMU_CAPS_BLOCKDEV)) {
        VIR_DEBUG("STR", jobname);
        goto cleanup;
    }

    if ((jobnewstate = qemuBlockjobConvertMonitorStatus(status)) == QEMU_BLOCKJOB_STATE_LAST)
        goto cleanup;

    if (!(job = virHashLookup(priv->blockjobs, jobname))) {
        VIR_DEBUG("STR", jobname);
        goto cleanup;
    }

    job->newstate = jobnewstate;

    if (job->synchronous) {
        VIR_DEBUG("STR", jobname);
        virDomainObjBroadcast(vm);
    } else {
        VIR_DEBUG("STR", jobname);
        processEvent = g_new0(struct qemuProcessEvent, 1);

        processEvent->eventType = QEMU_PROCESS_EVENT_JOB_STATUS_CHANGE;
        processEvent->vm = virObjectRef(vm);
        processEvent->data = virObjectRef(job);

        if (virThreadPoolSendJob(driver->workerPool, 0, processEvent) < 0) {
            virObjectUnref(vm);
            goto cleanup;
        }

        processEvent = NULL;
    }

 cleanup:
    qemuProcessEventFree(processEvent);
    virObjectUnlock(vm);
    return 0;
}