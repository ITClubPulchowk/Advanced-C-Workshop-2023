typedef struct Vec2
{
    int x, y;
} Vec2;
typedef struct Vec4
{
    union
    {
        struct
        {
            Vec2 a, b;
        };
        struct
        {
            int x, y, z, w;
        };
    };
} Vec4;

int main(int argc, char const *argv[])
{
    Vec2 p={1,2};
 Vec2 q={3,4};
 //Assign to vec4
 Vec4 r;
 r.a=p, r.b=q;
 //Check values for int x,y,z,w
 printf("x: %d, y: %d, z: %d, w: %d\n",r.x,r.y,r.z,r.w);
 printf("Address of x: %p, Address if a.x: %p\n",&r.x, &r.a.x );
    return 0;
}
