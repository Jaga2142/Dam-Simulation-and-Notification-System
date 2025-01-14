
#ifndef OUTLET_H
#define OUTLINE_H
#include"component.h"
class Outlet : protected Component
{
    private:
        int index;
    public:
        int max_outflowrate;
        int status;
        int outletvolume;
        Outlet(int i=0, int max=0, int s=0)
        {
            index =i;
            max_outflowrate= max;
            status = s;
            outletvolume = (max_outflowrate*status)/100;
        }
        virtual ~Outlet()
        {
            ;
        }
        virtual void display()const
        {
            cout << "Outlet " << index << ": ";
            if(status!=0)
                cout << max_outflowrate*status/100 << " m^3/s"<< endl;
            else
                cout << "Closed " << endl;
        }

        virtual void operate(int val=0,float p=0)           
        {
            if(val < 0 && val > 100)
                val = 0;
            status = val;
            outletvolume = (max_outflowrate*status)/100;
        }
};

#endif
