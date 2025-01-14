#include"Water.h"
#include<cmath>

Water :: Water(float p,int v)
{
    if(v >0)
    {
        pH=validatepH(p);
        volume = v;
    }
    else
    {
        pH=validatepH(p);
        volume=0;
    }
}

void Water :: operator += (const Water &oth)                 
    {if(oth.volume!=0)
        {
            float mol1=pow(10,-int(pH))*volume;
            float mol2=pow(10,-int(oth.pH))*oth.volume;    // mols of H+ ios in water
            int tvol = volume + oth.volume;     
            float tmol = mol1 + mol2;                   // total mols of H+ ions
            float tcon = tmol/tvol;                     // concentration of H+ in resultant solution
            float tpH = -log10(tcon);                   // pH=-log(conc(H+))
            volume = tvol;
            pH=tpH;
        }
    if(volume == 0)
    {
        volume = oth.volume;
        pH = oth.pH;
    }
}

void Water :: operator -= (const Water &oth)            // Removing a part water, no need to do ph calculation deducting volume is enough
{
    volume -= oth.volume;
}

float Water :: validatepH(float p)const                 // pH value should lie between (0-14)
{
    if(p<=0 && p >=14)
        return p;
    return 7;
}
