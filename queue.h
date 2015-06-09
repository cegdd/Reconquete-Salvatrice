#ifndef QUEUEH
#define QUEUEH


void Add_Creature_Queue(struct File *file, int nvNombre, int quantity);
int Read_Creature_Queue(struct File *file);
void Free_Queue_Element(struct File *file);
void initqueue(struct File *file, int ID);

#endif
