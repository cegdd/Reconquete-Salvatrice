#ifndef QUEUEH
#define QUEUEH

typedef struct Element Element;
typedef struct File File;

void Add_Creature_Queue(File *file, int nvNombre, int quantity);
int Read_Creature_Queue(File *file);
void initqueue(File *file, int ID);

struct Element
{
    int nombre;
    Element *suivant;
};

struct File
{
    Element *premier;
};

#endif
