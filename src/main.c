#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define MAXLINE 10000

struct termios cooked_mode;
struct termios raw_mode;

void enable_raw_mode(void);
void disable_raw_mode(void);

int main(void) {
    enable_raw_mode();
    
    char c;

    do {
        c = getchar();
        printf("You entered: %c\r\n", c);
    } while (c != 3);

    disable_raw_mode();
    return 0;
}

void enable_raw_mode(void) {
    tcgetattr(STDIN_FILENO, &cooked_mode);
    raw_mode = cooked_mode;
    raw_mode.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    raw_mode.c_oflag &= ~OPOST;
    raw_mode.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    raw_mode.c_cflag &= ~(CSIZE | PARENB);
    raw_mode.c_cflag |= CS8;
    
    tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
}

void disable_raw_mode(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &cooked_mode);
}
