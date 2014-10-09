#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int main()
{
#ifdef __ANDROID__
    assert(sizeof(double) == sizeof(long double));
#else
    assert(sizeof(double) <= sizeof(long double));
#endif

    double d = strtod("12.345678", NULL);
    long double ld = strtold("12.345678", NULL);

    printf("d = %f\n", d);
    printf("ld = %Lf\n", ld);

#ifdef __ANDROID__
    if ((long double)d != ld) {
#else
    if (fabsl(d - ld) > 0.000000000000001) {
#endif
        fprintf(stderr, "error: strtold produces unexpected result: %Lf (diff: %Lf)\n", ld, fabsl(d - ld));
        return 1;
    }

    _Exit(0);

    fprintf(stderr, "error: _Exit() function does not work\n");
    return 1;
}
