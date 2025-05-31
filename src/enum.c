typedef enum {
    RED,
    GREEN,
    BLUE,
    BLACK
} Color;

enum Day {
    SATURDAY = 1,
    SUNDAY = 2,
    MONDAY = 3,
    TUESDAY = 4,
    WEDNESDAY = 5,
    THURSDAY = 6,
    FRIDAY = 7
};

enum HttpStatus {
    STATUS_OK = 200,
    STATUS_NOT_FOUND = 404,
    STATUS_UNAUTHORIZED = 401,
    STATUS_FORBIDDEN = 403,
    STATUS_INTERNAL_SERVER_ERROR = 500
};

void invoker() {
    enum Day today = WEDNESDAY;

    printf("Today is day number: %d\n", today);

    Color favorite_color = BLUE;

    printf("My favorite color is: %d\n", favorite_color);
}
