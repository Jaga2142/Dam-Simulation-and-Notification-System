#include "Depth.h"

Depth :: Depth(int len, int wid, float lvl):Dimension(len,wid)
{
    length=(len>0)?len:0;
    breadth=(wid>0)?wid:0;
    maxdepth = (lvl>=0)?lvl:0;
    calculatearea();
    depth = new float* [length];
    if(length == 0 || breadth == 0)
        depth =nullptr;
    else
    {
        depth = new float* [length];
        for(int i=0; i<length; i++)
            depth[i]=new float [breadth];
    }
    
}

Depth :: ~Depth()                           // deallocation
{
    for(unsigned int i=0; i<length;i++)
        delete [] depth[i];
    delete [] depth;
}

Depth& Depth :: operator = (const Depth &s)
{
    if(this != &s)                      // checking if a object is equated to itself
    {
    length = s.length;
    breadth = s.breadth;
    maxdepth = s.maxdepth;
    depth = nullptr;
    depth = new float* [length];
    for(int i=0; i<length; i++)
        depth[i]=new float [breadth];
    for(int i=0; i<s.length; i++)
        for(int j=0; j < s.breadth; j++)
            depth[i][j] = s.depth[i][j];
    }
return *this;
}

Depth& Depth::reduce() const {
    static Depth nw;
    float rcompress = (length > 20) ? length / 20 : 1;
    float ccompress = (breadth > 20) ? breadth / 20 : 1;

    nw.length = (length > 20) ? 20 : length;
    nw.breadth = (breadth > 20) ? 20 : breadth;

    // Allocate memory for the reduced depth
    nw.depth = new float*[nw.length];
    for (int i = 0; i < nw.length; ++i) {
        nw.depth[i] = new float[nw.breadth];
    }

    // Fill the reduced matrix
    for (int ni = 0; ni < nw.length; ++ni) {
        for (int nj = 0; nj < nw.breadth; ++nj) {
            float temp = 0.0;
            for (int l = 0; l < int(rcompress); ++l) {
                for (int m = 0; m < int(ccompress); ++m) {
                    temp += depth[int(ni * rcompress + l)][int(nj * ccompress + m)];
                }
            }
            nw.depth[ni][nj] = temp / (rcompress * ccompress);
        }
    }
    return nw;
}


ostream& operator << (ostream &out, const Depth &dp)
{
    Depth op;
    op=dp.reduce();
    for(int i=0; i<op.length; i++)
    {
        out << "-----";
    }
    out << "---" << endl;
    for(int i=0; i<op.length; i++)
    {   
        out << "| ";
        for(int j=0; j < op.breadth; j++)
        {
            printf("%.2f ",op.depth[i][j]);
        }
        out << "|\n" ;
        if(i < op.length-1)
            cout << endl;
    }
    for(int i=0; i<op.length; i++)
    {
        out << "-----";
    }
    out << "---"<< endl;
return out;
}

istream& operator >> (istream &inp, Depth &dp)
{
    cin >> dp.maxdepth;
    dp.maxdepth = (dp.maxdepth >=0)?dp.maxdepth:0;
    for(int i=0; i<dp.length; i++)
    {  
        for(int j=0; j < dp.breadth; j++)
        {
            dp.depth[i][j]=dp.maxdepth;
        }
    }
return inp;
}

void Depth :: calculatemaxdepth()
{
    for(int i=0; i<length; i++)
        for(int j=0; j<breadth; j++)
            maxdepth+=depth[i][j];
    maxdepth/=(length*breadth);             //avg og depth matrix
}

Depth& Depth :: operator + (const int n)            // adds a integer to all elements in matrix
{
    try{
    for(int i=0; i<length; i++)
        for(int j=0; j<breadth; j++)
    {
        depth[i][j] += n;
        if(depth[i][j]<0)
         throw runtime_error("Negatives in depth parameters occured");
    }
    calculatemaxdepth();
    }catch(const exception& e) {
        cout << "Error during autopilot operation: " << e.what() << endl;

    }
return *this;
}

Depth& Depth :: operator - (const int n)            // subracts a integer to all elements in matrix
{
    *this + -n;
    return *this;
}

void Depth :: updatedepth (int l1, int l2)
{
    printf("updatedepth1called\n");
    if(l1 == length-1)                          //inlet is at the backside wall of the water storage
    {
        for(int i=length-3; i<=length-1; i++)
            for(int j=l2-2; j<=l2+2; j++)
            {
                depth[i][j]-=0.01 ;
            }
    }
    else if(l2 == breadth-1 || l2 == 0)         //inlet is at the right or left side wall the water storage
    {
        for(int i=(l1-2>=0)?l1-2:0 ; i<l1+3 && i < length && i >= 0; i++) // depth at area of shape square of size 5 is decreased due to deposition of sand from incoming water 
        {
            int j=(l2 == 0)?0:l2-4;
            for(int count=0; count<5; count++)
            {
                depth[i][j++]-=0.01 ;
            }
        }
    }
    calculatemaxdepth();
}

void Depth :: updatedepth (int outlet, float s)             // all outlets are assumed to be at front of the dam
{
    printf("UPdatedepth2called\n");
   int size = int(s);
    int partl = breadth/(size+1);       
    outlet = (outlet+1)*partl;
    for(int i=0; i<3; i++)
    {
        for(int j=outlet-1; j<=outlet+1 && j >=0 && j<breadth ; j++)    // area covered by a square of size 3 is affected due to erosion hence the depth increases 
        {
            depth[i][j] += 0.01;
        }
    }
    calculatemaxdepth();
}


