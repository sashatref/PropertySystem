#ifndef METATYPEDESTRUCTORBASE_H
#define METATYPEDESTRUCTORBASE_H

namespace PropertySystemNS
{

class MetaTypeDestructorBase
{
public:
    virtual ~MetaTypeDestructorBase() {}
    virtual void destruct(void *o) = 0;
};

template<class Type>
class MetaTypeDestructor : public MetaTypeDestructorBase
{
public:
    virtual void destruct(void *o) override
    {
        static_cast<Type*>(o)->~Type();
    }
};

}

#endif // METATYPEDESTRUCTORBASE_H
