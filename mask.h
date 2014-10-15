#ifndef MASK_H
#define MASK_H

#include <QString>

class Mask
{
    unsigned char _mask[128];
public:
    Mask();

    bool at(int i, int j) const;
    void change(int i, int j, bool value = true);
    void clear();
    QString data();
};

#endif // MASK_H
