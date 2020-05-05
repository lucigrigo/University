typedef struct {
    int id;
    char name[20];
    int minDmg,maxDmg,maxLife;
}Unit;

typedef struct {
    int id, currentLife;
}UnitPlayer;

typedef struct
{
        char* name;
        UnitPlayer *units;
        int nrUnits;
}Player;
