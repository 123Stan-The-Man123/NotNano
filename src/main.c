#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main(void) {
    struct termios cooked_mode, raw_mode;
    tcgetattr(STDIN_FILENO, &cooked_mode);
    raw_mode = cooked_mode;
    cfmakeraw(&raw_mode);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);

    char c;

    do {
        c = getchar();
        printf("You entered: %c\r\n", c);
    } while (c != 3);

    tcsetattr(STDIN_FILENO, TCSANOW, &cooked_mode);
    return 0;
}