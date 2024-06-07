static uint16_t nvme_identify_ns_csi(NvmeCtrl *n, NvmeRequest *req,
                                     bool active)
{
    NvmeNamespace *ns;
    NvmeIdentify *c = (NvmeIdentify *)&req->cmd;
    uint32_t nsid = le32_to_cpu(c->nsid);

    trace_pci_nvme_identify_ns_csi(nsid, c->csi);

    if (!nvme_nsid_valid(n, nsid) || nsid == NVME_NSID_BROADCAST) {
        return NVME_INVALID_NSID | NVME_DNR;
    }

    ns = nvme_ns(n, nsid);
    if (unlikely(!ns)) {
        if (!active) {
            ns = nvme_subsys_ns(n->subsys, nsid);
            if (!ns) {
                return nvme_rpt_empty_id_struct(n, req);
            }
        } else {
            return nvme_rpt_empty_id_struct(n, req);
        }
    }

    if (c->csi == NVME_CSI_NVM) {
        return nvme_rpt_empty_id_struct(n, req);
    } else if (c->csi == NVME_CSI_ZONED && ns->csi == NVME_CSI_ZONED) {
        return nvme_c2h(n, (uint8_t *)ns->id_ns_zoned, sizeof(NvmeIdNsZoned),
                        req);
    }

    return NVME_INVALID_FIELD | NVME_DNR;
}