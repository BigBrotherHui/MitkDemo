#ifndef UFUNBASEINIT_H
#define UFUNBASEINIT_H


class uFunBaseInit
{
public:
    static uFunBaseInit *getInStance();
    
private:
    explicit uFunBaseInit();
    static uFunBaseInit *self;
};

#endif // UFUNBASEINIT_H
