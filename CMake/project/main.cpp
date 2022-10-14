#include <iostream>
#include "config.h"

#ifdef USE_func
    #include "func.hpp"
#endif

int main(void)
{
    #ifdef USE_func
        hello();
        printf("Using customized lib. \n");
    #else
        printf("Using standard lib. \n");
    #endif

    return 0;
}
