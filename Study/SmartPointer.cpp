#include <iostream>
#include <memory>

using namespace std;

class Character
{
public:
    Character()
    {
    }

    ~Character()
    {
        cout << "no reference" << endl;
    }

    virtual void SetTarget(weak_ptr<Character> target)
    {
        this->target = target;
    }

private:
    weak_ptr<Character> target;
};

class Player : public Character
{
};

class Enemy : public Character
{
};

void avatar1()
{

    shared_ptr<Player> P1 = make_shared<Player>();
    shared_ptr<Enemy> E1 = make_shared<Enemy>();
    shared_ptr<Enemy> E2 = make_shared<Enemy>();

    P1->SetTarget(E1);
    E1->SetTarget(P1);
    E2->SetTarget(P1);

    cout << P1.use_count() << endl;
    cout << E1.use_count() << endl;
    cout << E2.use_count() << endl;
}

int main()
{
    avatar1();
}