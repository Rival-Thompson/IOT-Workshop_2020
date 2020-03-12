#include "Topics.hpp"

void Topics::getDeviceTopicByName(char *name, char *output)
{
  strcpy(output, deviceTopicBase);
  strcat(output, name);
}

char *Topics::deviceTopicBase = "workshopiot/device/";
char *Topics::topicBase = "workshopiot/base";