struct razer_report razer_chroma_standard_matrix_effect_breathing_dual(unsigned char variable_storage, unsigned char led_id, struct razer_rgb *rgb1, struct razer_rgb *rgb2)
{
    struct razer_report report = get_razer_report(0x03, 0x0A, 0x08);
    report.arguments[0] = 0x03; 
    report.arguments[1] = 0x02; 
    report.arguments[2] = rgb1->r;
    report.arguments[3] = rgb1->g;
    report.arguments[4] = rgb1->b;
    report.arguments[5] = rgb2->r;
    report.arguments[6] = rgb2->g;
    report.arguments[7] = rgb2->b;

    return report;
}