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


int main(int argc, char const *argv[])
{

    MyData data;
    float num =0.5;
    data.member_set=1;
    data.b=25.23;
    switch (data.member_set)
    {
    case 0:
        add_float_to_int(data,num);
        break;
    case 1:
    add_float_float(data,num);
    default:
        break;
    }
    return 0;
}
