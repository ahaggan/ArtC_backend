#include "artc.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    launch_menu();
    if (argc > 1) {
        if (strcmp(argv[1], "test") == 0) {
            test_parser();
        }
    }
    return 0;
}
