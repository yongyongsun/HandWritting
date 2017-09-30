#ifndef DATACALLBACK_H
#define DATACALLBACK_H

class DataCallback
{
public:
    virtual void dataActivated(int x, int y, int preasure) = 0;
};

#endif // DATACALLBACK_H
