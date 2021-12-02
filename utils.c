#include <string.h>
#include "utils.h"

int beginsWith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}
