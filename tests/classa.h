#ifndef CLASSA_H
#define CLASSA_H


class A
{
public:
    void Add(int y=0, int z=0)
    {
        std::cout << y << "," << z << std::endl;
    }
};

#define METAPROPERTY2(...) ->Add(__VA_ARGS__);

#endif // CLASSA_H
