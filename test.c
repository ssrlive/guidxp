#include <stdio.h>

#include "guidxp.h"


int main(int argc, char *argv[]) {
    char uuid[40] = { 0 };
    generate_guid(uuid, sizeof(uuid));
    printf("%s\n", uuid);
}
