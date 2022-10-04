#define SPIELER_BREITE 100
#define SPIELER_HOEHE 30
#define BALL_DURCHMESSER 20





int player_bewegen(int *y,int richtung)
{
    //richtung 1 == up
    //richtung 0 == down

    if(richtung == 0 && *y <= 1080)
    {
        *y += 2;
    }

    if(richtung == 1 && *y <= 0)
    {
        *y -= 2;
    }
}


