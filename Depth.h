#include"Dimension.h"
#include<iostream>
using namespace std;

class Depth : public Dimension
{
    private:
        float **depth;
    public:
        int area;
        Depth(int=0, int=0, float=0);
        ~Depth();
        friend ostream& operator << (ostream&, const Depth&);
        friend istream& operator >> (istream&, Depth&);
        int validatevolume(int);
        void calculatemaxdepth();           //does average of elements in discovery matrix
        void calculatearea()
        {
            area = length*breadth;
        }
        Depth& operator + (const int);      //to add depth of the dam also effects depth matrix
        Depth& operator - (const int);      // to reduce depth of the dam also effects depth matrix
        Depth& operator = (const Depth&);
        void updatedepth (int,int);         //to deposition of sediments in floor due to incoming water
        void updatedepth (int,float);       //to illustrate erosion process of dam's bed due to outflowing water
        Depth& reduce() const;         //to compress the depth matrix if size exceeds 20 and display it

};
