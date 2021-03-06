//
// Created by deren zhu on 2019/9/22.
//

#include <Python.h>
#include "headers/sample.h"

static int test = 10;
int test1 = 10;

void print_test() {
    printf("static test: %d\n", test);
    printf("test1: %d\n", test1);
}

/* int gcd(int, int) */
static PyObject* py_gcd(PyObject* self, PyObject* args) {
    int x, y, result;

    if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
        return NULL;
    }
    result = gcd(x, y);
    return Py_BuildValue("i", result);
}

/* int in_mandel(double, double, int) */
static PyObject* py_in_mandel(PyObject* self, PyObject* args) {
    double x0, y0;
    int n;
    int result;

    if (!PyArg_ParseTuple(args, "ddi", &x0, &y0, &n)) {
        return NULL;
    }
    result = in_mandel(x0, y0, n);
    return Py_BuildValue("i", result);
}

/* int divide(int, int, int*) */
static PyObject* py_divide(PyObject* self, PyObject* args) {
    int a, b, quotient, remainder;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return NULL;
    }
    quotient = divide(a, b, &remainder);
    return Py_BuildValue("(ii)", quotient, remainder);
}

/* Module method table */
//static PyMethodDef SampleMethods[] = {
//    PyModuleDef_HEAD_INIT,
//
//    "sample",           /* name of module */
//    "A sample module",  /* Doc string (may be NULL) */
//    -1,                 /* Size of per-interpreter state or -1 */
//    SampleMethods                /* Method table */
//};

/* Module initialization function */
//PyMODINIT_FUNC PyInit_sample(void) {
//    return PyModule_Create(&samplemodule);
//}