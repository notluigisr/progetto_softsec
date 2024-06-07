static void latencyModePrint(long long min, long long max, double avg, long long count) {
    if (config.output == OUTPUT_STANDARD) {
        printf("STR",
                min, max, avg, count);
        fflush(stdout);
    } else if (config.output == OUTPUT_CSV) {
        printf("STR", min, max, avg, count);
    } else if (config.output == OUTPUT_RAW) {
        printf("STR", min, max, avg, count);
    }
}