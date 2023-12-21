typedef struct MyData
{
    union
    {
        int a;
        float b;
    };
        int member_set; // 0 for int, 1 for float
} MyData;


float add_float_float(MyData a, float b)
{
    return a.b+b;
}

float add_float_to_int(MyData a, float b)
{
    return a.a+b;
}

typedef float (*add_function) (MyData,float);

int main(int argc, char const *argv[])
{
    add_function functions[]={add_float_to_int,add_float_float};
    MyData data;
    data.member_set=0;
    data.a=5;
    functions[data.member_set](data,0.5);
    return 0;
}
