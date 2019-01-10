#ifndef MYSTRINGLIST_H
#define MYSTRINGLIST_H

#include "src/01_LinearList/linklist.h"

class String;
class StringList : public LinkList<String>
{
public:
    StringList();
};

#endif // MYSTRINGLIST_H
