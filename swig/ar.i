/* module */
%module ar
%include "carrays.i"
%include "stdint.i"
%include "typemaps.i"
%include "cdata.i"

%array_class(double, double_array);

/* C wrapper */
%{
#include "ar.h"
%}

/* */
void AutoRegressionPy(double *inputseries, int length, int degree,
                      double *coefficients, int method);
