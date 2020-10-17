#ifndef KEYS_H
# define KEYS_H
# if defined(__MACH__)
#  define KEY_ESC 53
#  define KEY_C 8
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_RIGHT 124
#  define KEY_LEFT 123
#  define KEY_U 32
#  define KEY_D 2
#  define KEY_8 91
#  define KEY_4 86
#  define KEY_6 88
#  define KEY_2 84
# elif defined(__linux__)
#  define KEY_ESC 65307
#  define KEY_C 99
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_RIGHT 65363
#  define KEY_LEFT 65361
#  define KEY_U 117
#  define KEY_D 100
#  define KEY_8 65431
#  define KEY_4 65430
#  define KEY_6 65432
#  define KEY_2 65433
# endif
#endif