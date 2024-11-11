#include<vector>
#include<cstring>
#include"Depth.h"
#include"Water.h"
#include"Inlet.h"
#include"Outlet.h"

class Dam 
{
    private:
        const string Name;
        const string Location;
        float current_water_level;
        Depth depth;
        Water damwater;

    public:
        vector <Inlet> I;
        vector <Outlet> O;
        Dam(const string&,const string&, int=0, int=0, int=0, int=0, float = 7, int =0);
        // no destructor drequired as all members are statically allocated
        friend ostream& operator << (ostream&,const Dam&);
        friend istream& operator >> (istream&, Dam&);
        int validatevolume(int) const;
        bool validatecoordinates(const int,const int,int,int)const; //to check if coordinates of inlets are valid
        bool addinletwater(Inlet&);
        bool reduceoutletwater(Outlet&);    // reduce the water going out from dam water
        void adddepth(int);
        void Addoutlet();
        void Addinlet();
        void simulate(int);
        void autopilot();
        bool checkdam();    //returns false if dam is full or dry  
        
};