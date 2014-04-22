#include "ai.h"
#include "fool.h"

int main()
{
    int i;
    classFool AI[4];
    for (i = 0; i < 4; ++i)
    {
        foolConstruct(&AI[i], 1.f, 1.f);
    }

    return 0;
}