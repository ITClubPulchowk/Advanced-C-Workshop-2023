typedef struct Position
{
    int x;
    int y;
} Position;

// Circle and square shapes
typedef struct Circle
{
    int radius;
    Position center;
} Circle;

typedef struct Square
{
    int length;
    Position center;
} Square;
// Object shape enum


typedef enum Object_shape
{
    Object_shape_circle,
    Object_shape_square
} Object_shape;

// Object structure
typedef struct Object
{
    Object_shape shape;
    union
    {
        Circle c;
        Square s;
    };
} Object;