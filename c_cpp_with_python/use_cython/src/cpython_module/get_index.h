/* Generated by Cython 0.29.6 */

#ifndef __PYX_HAVE__get_index
#define __PYX_HAVE__get_index


#ifndef __PYX_HAVE_API__get_index

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#ifndef DL_IMPORT
  #define DL_IMPORT(_T) _T
#endif

__PYX_EXTERN_C PyObject *get_index(PyObject *, PyObject *);

#endif /* !__PYX_HAVE_API__get_index */

/* WARNING: the interface of the module init function changed in CPython 3.5. */
/* It now returns a PyModuleDef instance instead of a PyModule instance. */

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initget_index(void);
#else
PyMODINIT_FUNC PyInit_get_index(void);
#endif

#endif /* !__PYX_HAVE__get_index */
