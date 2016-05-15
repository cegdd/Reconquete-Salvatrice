

int map (struct DIVERSsysteme *systeme,struct typeFORthreads *online,struct PACKbouton *bouton ,struct PACKobjet *objet,
        struct PACKmonstre *monstre,struct PERSO *perso,struct DIVERSinventaire *inventaire,struct DIVERSdeplacement *deplacement,
		struct DIVERStemps *temps,struct DIVERSui *ui,struct DIVERSchat *chat,struct DIVERScraft *craft,struct DIVERSmap *carte,
		struct PACKpnj *pnj,struct PACKrecompense *recompense,struct typeFORevent *FORevent);
int lancementcombat(struct PACKmonstre *monstre,struct DIVERSinventaire *inventaire,struct DIVERSui *ui,
                    struct DIVERSdeplacement *deplacement,struct PACKobjet *objet,struct PERSO *perso,struct DIVERSsysteme *systeme,
                    struct PACKrecompense *recompense, bool arcademode);
void detectioncombat(struct PACKmonstre *monstre,struct DIVERSinventaire *inventaire,struct DIVERSui *ui,
					struct DIVERSdeplacement *deplacement,struct PACKobjet *objet,struct PERSO *perso,struct DIVERSsysteme *systeme,
					struct PACKrecompense *recompense, bool arcademode);

void ANIMmonstre(struct PACKmonstre *monstre,struct DIVERStemps *temps);

void gestionchat(struct DIVERSchat *chat,struct DIVERSsysteme *systeme,struct typeFORthreads *online);
void sinchronisation(struct PACKpnj *pnj,struct DIVERSmap *carte,struct PACKmonstre *monstre,struct DIVERScraft *craft,
                     struct DIVERSsysteme *systeme,struct typeFORthreads *online,struct PERSO *perso);

int calcultempssecondes(int temptotal);
int calcultempsminutes(int temptotal);
int calcultempsheures(int temptotal);
int calcultempsjours(int temptotal);
