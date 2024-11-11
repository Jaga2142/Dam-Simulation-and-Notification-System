class Inlet
{
    public:
        int index;
        int inlocation[2];
        int inflowrate;
        float incoming_pH;
        Inlet(int i=0, int l1=0, int l2=0)
        {
            index = i;
            inflowrate=incoming_pH=0;
            inlocation[0]=l1;
            inlocation[1]=l2;
        }
        // no destructor drequired as all members are statically allocated
        void input(int val,int pval)            //user need to enter parameters of inlet which are taken from physical instruments
        {
            if(val >=0 )
                inflowrate = val;
            else 
                inflowrate = 0;
            if(pval >=0 && pval <=14)
                incoming_pH = pval;
            else 
                incoming_pH = 7;
        }
};
