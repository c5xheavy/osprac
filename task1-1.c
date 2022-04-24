#include <stdio.h>
#include <unistd.h>

int main() {
    uid_t uid = getuid();
    gid_t gid = getgid();

    printf("User ID: %i\nGroup ID: %i\n", uid, gid);

    return 0;
}

