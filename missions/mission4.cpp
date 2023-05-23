#include "./missions.h"


void refreshDataBase(System& airports, vector<string>paths)
{
    airports.regenerate_db();
}