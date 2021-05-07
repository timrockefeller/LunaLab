#include <iostream>
#include <Common/Visitor.h>
using namespace std;
using namespace KTKR;

class IFigure
{
public:
    virtual ~IFigure(){};
};

class Sphere : public IFigure
{
public:
    int x = 12;
};

class Polygon : public IFigure
{
public:
    int y = 14;
};
using DerivedClass = std::tuple<Sphere, Polygon>;
class Drawer : public GeneralVisitor<Drawer, IFigure, DerivedClass, void()>
{
public:
    Drawer() = default;
    void ImplVisit(Sphere *p)
    {
        cout << "Sphere:" << p->x << endl;
    }
    void ImplVisit(Polygon *p)
    {
        cout << "Polygon:" << p->y << endl;
    }
};
class SharedDrawer : public SharedVisitor<SharedDrawer, IFigure, DerivedClass, void()>
{
public:
    SharedDrawer() = default;
    void ImplVisit(Ptr<Sphere> p)
    {
        cout << "Sphere:" << p->x << endl;
    }
    void ImplVisit(Ptr<Polygon> p)
    {
        cout << "Polygon:" << p->y << endl;
    }
};
int main()
{
    Drawer dvisitor;
    SharedDrawer svisitor;
    IFigure *s = new Sphere();
    IFigure *p = new Polygon();
    Ptr<IFigure> ss = std::make_shared<Sphere>();
    Ptr<IFigure> sp = std::make_shared<Polygon>();
    dvisitor.Visit(s);
    dvisitor.Visit(p);
    svisitor.Visit(ss);
    svisitor.Visit(sp);
    return 0;
}