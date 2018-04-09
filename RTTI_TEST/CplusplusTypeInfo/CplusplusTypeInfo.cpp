#include <iostream>

using namespace std;

class BaseClass
{
public:
    int iValue;
    BaseClass()
    {
        cout << "BaseClass is constructed..." << endl;
    }
    virtual void Print()
    {
        cout << "BaseClass --> Print ..." << endl;
    }
};

class DeriveClass :public BaseClass
{
public:
    float fValue;
    DeriveClass()
    {
        cout << "DeriveClass is constructed..." << endl;
    }
    void Print()
    {
        cout << "DeriveClass --> Print ..." << endl;
    }
};

void CheckObjType(BaseClass* pObj);

int main(int argc, char **argv)
{
    cout << "=====================  typeid erros  ====================" << endl;

    BaseClass bc;
    DeriveClass dc;

    BaseClass *pBaseDerive = new DeriveClass();

    CheckObjType(&bc);
    CheckObjType(&dc);
    CheckObjType(pBaseDerive);

    return 0;
}

void CheckObjType(BaseClass* pObj)
{
    // ���ڶ�̬��polymorphic�����ɳɹ�
    // �� BaseClass �в����� virtual function�����Խ�ʧ�ܣ�û�ж�̬�����������벻ͨ����
    if (typeid(*pObj) == typeid(DeriveClass))
    {
        DeriveClass *pDerive = dynamic_cast<DeriveClass*>(pObj);
        pDerive->Print();
        cout << "Bingo DeriveClass... name=" << typeid(pObj).name() << "   *name=" << typeid(*pObj).name() << endl;
    }
    else if (typeid(*pObj) == typeid(BaseClass))
    {
        BaseClass *pBase = dynamic_cast<BaseClass*>(pObj);
        pBase->Print();

        cout << "Bingo BaseClass... name=" << typeid(pObj).name() << "   *name=" << typeid(*pObj).name() << endl;
    }
    else
    {
        cout << "unknown type --> " << typeid(pObj).name() << endl;
        cout << "unknown type --> " << typeid(*pObj).name() << endl;
    }
}
