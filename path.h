#ifndef PATHH
#define PATHH


#include <stdbool.h>

#include "image.h"

#define PATH_dots 16


struct PATH
{
    int x[PATH_dots];
    int y[PATH_dots];
    bool used[PATH_dots];
    bool loop;
    int counter;
};

//int PATH_add(struct PATH *path, int x, int y, struct DATA *data);
//int PATH_remove(struct PATH *path);
void PATH_init(struct PATH *path);
//void PATH_write(struct PATH *path);
//void PATH_display (struct DATA *data);

#endif
