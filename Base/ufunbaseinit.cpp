#include "ufunbaseinit.h"
#include <QSettings>
#include <QDebug>
#include "ustatus.h"

uFunBaseInit *uFunBaseInit::self = nullptr;

uFunBaseInit::uFunBaseInit()
{
    ;
}

uFunBaseInit * uFunBaseInit::getInStance()
{
    if (self == nullptr)
    {
        if (self == nullptr)
        {
            self = new uFunBaseInit;
        }
    }
    return self;
}

