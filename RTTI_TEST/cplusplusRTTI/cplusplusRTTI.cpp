/**************************************************************************
    1. typeid      ：返回指针或引用所指对象的实际类型。
    2. dynamic_cast：将基类类型的指针或引用安全的转换为派生类型的指针或引用。
***************************************************************************/

#include <iostream>

using namespace std;

class Movable
{
public:
    Movable()
    {
        cout << "Movable constructed..." << endl;
    }
    virtual void move() = 0;
};

class Bus :public Movable
{
public:
    Bus()
    {
        cout << "Bus constructed..." << endl;
    }
    virtual void move()
    {
        cout << "Bus --> move" << endl;
    }
    void carry()
    {
        cout << "Bus --> carry" << endl;
    }
};

class Tank :public Movable
{
public:
    Tank()
    {
        cout << "Tank constructed..." << endl;
    }
    virtual void move()
    {
        cout << "Tank --> move" << endl;
    }
    void fire()
    {
        cout << "Tank --> fire" << endl;
    }
};

void CheckObjType(Movable &obj);
void CheckObjType(Movable *obj);

int main(int argc, char** argv)
{
    cout << "=====================    typeid    ====================" << endl;
    cout << "===================== dynamic_cast ====================" << endl;

    char a = 0;
    short b = 0;
    int c = 0;
    float d = 0;
    double e = 0;

    cout << "char   a --> typeid(a) == " << typeid(a).name() << endl
        << "short  b --> typeid(b) == " << typeid(b).name() << endl
        << "int    c --> typeid(c) == " << typeid(c).name() << endl
        << "float  d --> typeid(d) == " << typeid(d).name() << endl
        << "double e --> typeid(e) == " << typeid(e).name() << endl;

    Bus bus;
    Tank tank;

    CheckObjType(bus);
    CheckObjType(tank);

    cout << "=======================================================" << endl;
    CheckObjType(&bus);
    CheckObjType(&tank);

    return 0;
}

void CheckObjType(Movable &obj)
{
    obj.move();

    if (typeid(obj) == typeid(Bus))
    {
        Bus bus = dynamic_cast<Bus&>(obj);
        bus.carry();
    }
    else if (typeid(obj) == typeid(Tank))
    {
        Tank tank = dynamic_cast<Tank&>(obj);
        tank.fire();
    }
    else
    {
        cout << "unknow type --> " << typeid(obj).name() << endl;
    }
}

void CheckObjType(Movable *obj)
{
    obj->move();

    if (typeid(*obj) == typeid(Bus))
    {
        Bus *pBus = dynamic_cast<Bus*>(obj);
        pBus->carry();
    }
    else if (typeid(*obj) == typeid(Tank))
    {
        Tank *pTank = dynamic_cast<Tank*>(obj);
        pTank->fire();
    }
    else
    {
        cout << "unknow type --> " << typeid(obj).name() << endl;
    }
}
