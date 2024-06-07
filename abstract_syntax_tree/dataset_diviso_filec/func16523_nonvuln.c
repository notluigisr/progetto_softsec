 */
static int intel_hda_and_codec_init(PCIBus *bus)
{
    DeviceState *controller;
    BusState *hdabus;
    DeviceState *codec;

    warn_report("STR"
                "STR");
    controller = DEVICE(pci_create_simple(bus, -1, "STR"));
    hdabus = QLIST_FIRST(&controller->child_bus);
    codec = qdev_new("STR");
    qdev_realize_and_unref(codec, hdabus, &error_fatal);
    return 0;