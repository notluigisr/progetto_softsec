struct razer_report razer_chroma_standard_set_led_state(unsigned char variable_storage, unsigned char led_id, unsigned char led_state)
{
    struct razer_report report = get_razer_report(0x03, 0x00, 0x03);
    report.arguments[0] = variable_storage;
    report.arguments[1] = led_id;
    report.arguments[2] = clamp_u8(led_state, 0x00, 0x01);

    return report;
}