typedef struct BOUTON BOUTON;
typedef struct CHOSE CHOSE;
typedef struct EMPLACEMENT EMPLACEMENT;
typedef struct PLAN PLAN;
typedef struct PERSO PERSO;
typedef struct PACKobjet PACKobjet;
typedef struct PACKbouton PACKbouton;
typedef struct PACKmonstre PACKmonstre;
typedef struct DIVERSinventaire DIVERSinventaire;
typedef struct DIVERSdeplacement DIVERSdeplacement;
typedef struct DIVERStemps DIVERStemps;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct DIVERSui DIVERSui;
typedef struct DIVERSchat DIVERSchat;
typedef struct DIVERScraft DIVERScraft;
typedef struct DIVERSmap DIVERSmap;
typedef struct PACKpnj PACKpnj;
typedef struct PACKrecompense PACKrecompense;
typedef struct typeFORevent typeFORevent;
typedef struct typeFORthreads typeFORthreads;

int map (DIVERSsysteme *systeme, typeFORthreads *online, PACKbouton *bouton , PACKobjet *objet, PACKmonstre *monstre, PERSO *perso, DIVERSinventaire *inventaire, DIVERSdeplacement *deplacement, 
		DIVERStemps *temps, DIVERSui *ui, DIVERSchat *chat, DIVERScraft *craft, DIVERSmap *carte, PACKpnj *pnj, PACKrecompense *recompense, typeFORevent *FORevent);
int lancementcombat(PACKmonstre *monstre, DIVERSinventaire *inventaire, DIVERSchat *chat, DIVERSui *ui,
                     DIVERSdeplacement *deplacement, PACKobjet *objet, PERSO *perso,DIVERSsysteme *systeme,
                     PACKrecompense *recompense, bool arcademode);
void detectioncombat(PACKmonstre *monstre, DIVERSinventaire *inventaire, DIVERSchat *chat, DIVERSui *ui,
					DIVERSdeplacement *deplacement, PACKobjet *objet, PERSO *perso, DIVERSsysteme *systeme,
					PACKrecompense *recompense, bool arcademode);

void ANIMpersomarche(DIVERSdeplacement *deplacement, DIVERStemps *temps);
void ANIMmonstre(PACKmonstre *monstre, DIVERStemps *temps);

void gestionchat(DIVERSchat *chat, DIVERSsysteme *systeme, typeFORthreads *online);
void sinchronisation(PACKpnj *pnj, DIVERSmap *carte, PACKmonstre *monstre, DIVERScraft *craft, DIVERSsysteme *systeme
							, typeFORthreads *online, PERSO *perso);

int calcultempssecondes(int temptotal);
int calcultempsminutes(int temptotal);
int calcultempsheures(int temptotal);
int calcultempsjours(int temptotal);
