int auth (char sauvegarde[][50]);
int login (struct DIVERSsysteme *systeme);
int creerjoueur(char sauvegarde[][50]);

void InitLoginStore (struct typelogin *loginstore,struct DIVERSsysteme *systeme);
void Initbouton     (struct typelogin *loginstore,struct DIVERSsysteme *systeme);
void affichageloggin(struct typelogin *loginstore,struct DIVERSsysteme *systeme);
