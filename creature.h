#ifndef CREATUREH
#define CREATUREH


struct CREATURE
{
    bool aggressif;

    int vie;
    int Rvision;
    int vitesse;
    int dps;
    int Ratk;
    int hitlaps;

    char name[64];
    char imgpath[128];

    struct pict pict;
};

void initcreature(struct CREATURE *creature);

#endif
