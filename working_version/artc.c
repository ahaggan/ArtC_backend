#include "artc.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc > 1 && strcmp(argv[1], "test") == 0) {
            test_parser();
    }

    launch_menu();

    return 0;
}
