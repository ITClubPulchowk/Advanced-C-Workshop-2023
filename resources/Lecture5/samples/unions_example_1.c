typedef struct MyData
{
    union
    {
        int a;
        float b;
    };
} MyData;

int main(int argc, char const *argv[])
{
    MyData data;
    data.a = 4000;
    data.b = 3453.25f;
    printf("%f, %d\n", data.b, data.a);
    printf("%p, %p\n", &data.b, &data.a);
    return 0;
}
