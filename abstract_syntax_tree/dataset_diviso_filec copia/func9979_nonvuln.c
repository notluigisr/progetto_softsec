rectangle_intersect (gint ax, gint ay, gint awidth, gint aheight,
                     gint bx, gint by, gint bwidth, gint bheight,
                     gint *rx, gint *ry, gint *rwidth, gint *rheight)
{
    gint rx1, ry1, rx2, ry2;

    rx1 = MAX (ax, bx);
    ry1 = MAX (ay, by);
    rx2 = MIN (ax + awidth, bx + bwidth);
    ry2 = MIN (ay + aheight, by + bheight);

    if (rx2 > rx1 && ry2 > ry1) {
        *rx = rx1;
        *ry = ry1;
        *rwidth = rx2 - rx1;
        *rheight = ry2 - ry1;

        return TRUE;
    } else {
        *rx = *ry = *rwidth = *rheight = 0;

        return FALSE;
    }
}