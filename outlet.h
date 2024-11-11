class Outlet
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
        // no destructor drequired as all members are statically allocated
        void operate()                  // open or closes the outlet gate
        {
            int val=0;
            cout << "0-close ,(1-100)-open percentage: ";
            cin >> val;
            if(val < 0 && val > 100)
                val =0;
            status = val;
            outletvolume = (max_outflowrate*status)/100;
        }
        void operate(int val)           
        {
            if(val < 0 && val > 100)
                val = 0;
            status = val;
            outletvolume = (max_outflowrate*status)/100;
        }
};

