class Dimension 
{
   protected:
        int length;
        int breadth;
    public:
        float maxdepth;
        Dimension(int l=0, int b=0, float d=0)
        {
            if(l>=0 && b >= 0 && d >=0)
            {
                length = l;
                breadth = b;
                maxdepth =d;
            }
            else
                length = breadth = maxdepth =0;
        }
        // no destructor drequired as all members are statically allocated
};

