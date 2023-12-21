typedef struct MyData
{
    union
    {
        int a;
        float b;
    };
        int member_set; // 0 for int, 1 for float
} MyData;


