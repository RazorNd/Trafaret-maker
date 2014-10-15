#include "mask.h"
#include <QDebug>

Mask::Mask()
{    
    clear();
}

bool Mask::at(int i, int j) const
{
    if(i < 32 && j < 32 && i >= 0 && j >= 0)
    {
        int numByte = (i / 8) + (j * 4);
        int numBit = i % 8;
        return (_mask[numByte] & (1 << (7 - numBit)));
    }
    return false;
}

void Mask::change(int i, int j, bool value)
{
    if(i < 32 && j < 32 && i >= 0 && j >= 0)
    {
        int numByte = (i / 8) + (j * 4);
        int numBit = i % 8;
        if(value)
        {

            _mask[numByte] |= (1 << (7 - numBit));

        }
        else
        {
            _mask[numByte] &= ~(1 << (7 - numBit));
        }
    }
}

void Mask::clear()
{
    for(int i = 0; i < 128; i++)
    {
        _mask[i] = 0;
    }
}

QString Mask::data()
{
    QString str = "{\n";
    for(int i = 0, numWordInLine = 1; i < 128; i++, numWordInLine++)
    {
        str += " 0x" + QString::number(_mask[i], 16) + ",";
        if( !(numWordInLine % 8))
        {
            str += "\n";
        }
    }
    str += "}";    
    return str;
}

