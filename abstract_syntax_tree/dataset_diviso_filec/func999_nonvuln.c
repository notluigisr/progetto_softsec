struct razer_report razer_chroma_extended_matrix_effect_starlight_random(unsigned char variable_storage, unsigned char led_id, unsigned char speed)
{
    struct razer_report report = razer_chroma_extended_matrix_effect_base(0x06, variable_storage, led_id, 0x07);

    speed = clamp_u8(speed, 0x01, 0x03);

    report.arguments[4] = speed;
    return report;
}