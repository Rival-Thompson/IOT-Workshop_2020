
#ifndef Topic_H
#define Topic_H

#include "Arduino.h"

class Topics
{
    public:
        static char* deviceTopicBase;
        static char* topicBase;
        static void getDeviceTopicByName(char * name, char * output);
};

#endif