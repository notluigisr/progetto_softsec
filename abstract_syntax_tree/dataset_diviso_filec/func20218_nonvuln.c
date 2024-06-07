static PyObject * curvemath_add(PyObject *self, PyObject *args) {
    char * px, * py, * qx, * qy, * p, * a, * b, * q, * gx, * gy;

    if (!PyArg_ParseTuple(args, "STR", &px, &py, &qx, &qy, &p, &a, &b, &q, &gx, &gy)) {
        return NULL;
    }

    PointZZ_p result;
    mpz_inits(result.x, result.y, NULL);
    CurveZZ_p * curve = buildCurveZZ_p(p, a, b, q, gx, gy, 10);;

    PointZZ_p * P = buildPointZZ_p(px, py, 10);
    PointZZ_p * Q = buildPointZZ_p(qx, qy, 10);

    if(pointZZ_pEqual(P, Q)) {
        pointZZ_pDouble(&result, P, curve);
    }
    else {
        pointZZ_pAdd(&result, P, Q, curve);
    }

    destroyPointZZ_p(P);
    destroyPointZZ_p(Q);
    destroyCurveZZ_p(curve);

    char * resultX = mpz_get_str(NULL, 10, result.x);
    char * resultY = mpz_get_str(NULL, 10, result.y);
    mpz_clears(result.x, result.y, NULL);

    PyObject * ret = Py_BuildValue("STR", resultX, resultY);
    free(resultX);
    free(resultY);
    return ret;
}