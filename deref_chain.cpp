struct A {
    int foo, bar;
};

struct B {
    A a;
    A *operator->() { return &a; }
};

struct C {
    B b;
    B operator->() { return b; }
};

struct D {
    C c;
    C operator->() { return c; }
};
