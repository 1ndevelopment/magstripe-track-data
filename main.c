#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

static char key_map[][3] = {
    {KEY_1,          '1', '!'},
    {KEY_2,          '2', '@'},
    {KEY_3,          '3', '#'},
    {KEY_4,          '4', '$'},
    {KEY_5,          '5', '%'},
    {KEY_6,          '6', '^'},
    {KEY_7,          '7', '&'},
    {KEY_8,          '8', '*'},
    {KEY_9,          '9', '('},
    {KEY_0,          '0', ')'},
    {KEY_MINUS,      '-', '_'},
    {KEY_EQUAL,      '=', '+'},
    {KEY_Q,          'q', 'Q'},
    {KEY_W,          'w', 'W'},
    {KEY_E,          'e', 'E'},
    {KEY_R,          'r', 'R'},
    {KEY_T,          't', 'T'},
    {KEY_Y,          'y', 'Y'},
    {KEY_U,          'u', 'U'},
    {KEY_I,          'i', 'I'},
    {KEY_O,          'o', 'O'},
    {KEY_P,          'p', 'P'},
    {KEY_LEFTBRACE,  '[', ']'},
    {KEY_RIGHTBRACE, '{', '}'},
    {KEY_ENTER,      '\n', '\n'},
    {KEY_A,          'a', 'A'},
    {KEY_S,          's', 'S'},
    {KEY_D,          'd', 'D'},
    {KEY_F,          'f', 'F'},
    {KEY_G,          'g', 'G'},
    {KEY_H,          'h', 'H'},
    {KEY_J,          'j', 'J'},
    {KEY_K,          'k', 'K'},
    {KEY_L,          'l', 'L'},
    {KEY_SEMICOLON,  ';', ':'},
    {KEY_APOSTROPHE, '\'', '"'},
    {KEY_GRAVE,      '`', '~'},
    {KEY_BACKSLASH,  '\\', '|'},
    {KEY_Z,          'z', 'Z'},
    {KEY_X,          'x', 'X'},
    {KEY_C,          'c', 'C'},
    {KEY_V,          'v', 'V'},
    {KEY_B,          'b', 'B'},
    {KEY_N,          'n', 'N'},
    {KEY_M,          'm', 'M'},
    {KEY_COMMA,      ',', '<'},
    {KEY_DOT,        '.', '>'},
    {KEY_SLASH,      '/', '?'},
    {KEY_SPACE,      ' ', ' '}
};

static char
find_key(int c, int shift)
{
    for (int i = 0; i < sizeof key_map; i++) {
        if (key_map[i][0] == c) {
            if (shift) {
                return key_map[i][2];
            } else {
                return key_map[i][1];
            }
        }
    }
    return -1;
}

#define KEY_UP_ACTION   0
#define KEY_DOWN_ACTION 1

static void
read_event(int fd) {
    int shift = 0;
    for (;;) {
        struct input_event ev;
        if (read(fd, &ev, sizeof(ev)) != sizeof(ev)) {
            exit(1);
        }

        switch(ev.type) {
        case EV_KEY:
            if ((ev.code == KEY_LEFTSHIFT) || (ev.code == KEY_RIGHTSHIFT)) {
                shift = !shift;
                continue;
            }
            if (ev.value == KEY_UP_ACTION) {
                 continue;
            }

            int key;
            if (0 < (key = find_key(ev.code, shift))) {
                printf("%c", key);
            } else {
                printf("%d", ev.code);
            }
            break;
        default:
            break;
        }
    }
}

static void
die(const char *s)
{
    perror(s);
    exit(1);
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "%s: '/dev/input/event?' not given\n", argv[0]);
        exit(1);
    }

    const char *dev = argv[1];
    int fd = open(dev, O_RDONLY);
    if (fd < 0) die(dev);

    read_event(fd);

    if (close(fd) < 0) die(dev);
    return 0;
}
