static void __init acpi_sci_ioapic_setup(u8 bus_irq, u16 polarity, u16 trigger, u32 gsi)
{
	if (trigger == 0)	
		trigger = 3;

	if (polarity == 0)	
		polarity = 3;

	
	if (acpi_sci_flags & ACPI_MADT_TRIGGER_MASK)
		trigger = (acpi_sci_flags & ACPI_MADT_TRIGGER_MASK) >> 2;

	if (acpi_sci_flags & ACPI_MADT_POLARITY_MASK)
		polarity = acpi_sci_flags & ACPI_MADT_POLARITY_MASK;

	mp_override_legacy_irq(bus_irq, polarity, trigger, gsi);
	acpi_penalize_sci_irq(bus_irq, trigger, polarity);

	
	acpi_sci_override_gsi = gsi;
	return;
}