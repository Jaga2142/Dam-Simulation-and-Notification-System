#include"Dam.h"
#include<ctime>             // to make delay during simulation

Dam :: Dam(const string &n,const string &l, int in, int o,int len, int wid, float p, int v ):Name(n),Location(l),depth(len,wid),damwater(p,v)
{
    
    for(int i=0; i<in; i++)
    {
        int x,y;
        while(true)
        {
            cout << "Enter location of inlet "<< i << " in depth coordinates: ";
            cin >> x >> y;
            if(validatecoordinates(len,wid,x,y))
                break;
            cout << "Invalid coordinates for inlet!!!\nRe-";
        }
        Inlet temp(i,x,y);  
        I.push_back(temp);
    }
    int max;
    cout << "Enter Max water discharge of outlets: ";
    cin >> max;
    for(int i=0; i<o; i++)
    {
        Outlet temp(i,max,0);
        O.push_back(temp);
    }
}

bool Dam :: validatecoordinates(const int l, const int w, int x, int y)const
{
    if(x==l-1 && y>=0 && y<w)           //inlet should either be at the backside walls of the water storage or at right or left side walls
        return true;
    if((y==0 && x>0 && x<l) || (y == w-1 && x>0 && x<l))
        return true;
return false;
}

ostream& operator << (ostream &out,const Dam &D)
{
    out << "\n##############################################\nName         : ";
    for(int i=0; D.Name[i]!= '\0'; i++)
        out << D.Name[i];
    out << "\nLocation     : ";
    for(int i=0; D.Location[i]!= '\0'; i++)
        out << D.Location[i];
    out << "\nWater Stored : " << D.damwater.volume << " m^3" << endl;
    out << "pH of water  : " << D.damwater.pH << endl;
    out << "Water Level  : " << D.current_water_level << " m/";
    printf("%.2f m",D.depth.maxdepth);
    out << endl;
    out << "Inlets water supply:" << endl;
    for(int i=0; i<D.I.size(); i++)
        D.I[i].display();
    out << "\nOutlets water discharge:" << endl;
    for(int i=0; i<D.O.size(); i++)
        D.O[i].display();
    out << "\nDepth matrix(in metres):\n" << D.depth << endl;
return out;
}

istream& operator >> (istream &inp, Dam &D)
{
    cout << "Enter maxdepth of dam: ";
    inp >> D.depth;
    cout << "Initial water stored and pH: ";
    int w;
    float p;
    inp >> w >> p;
    D.damwater.pH = D.damwater.validatepH(p);
    D.damwater.volume = D.validatevolume(w);
    D.current_water_level =  float(D.damwater.volume) / (D.depth.area);
return inp;
}

int Dam :: validatevolume(int w)const
{
    if(w<0)
    {
        cout << "volume cannot be negative assigned 0 "<< endl;
        return 0;
    }
    else if(w > (depth.area*depth.maxdepth))
    {
        cout << "Water more than dam can store is given, volume is now assigned full"<<endl;
        return depth.area*depth.maxdepth;
    }
return w;
}

bool Dam :: addinletwater(Inlet &I)
{
    Water sub(I.incoming_pH,I.inflowrate);
    damwater+=sub;                  // calling overloaded operator 
    current_water_level += I.inflowrate/(depth.area); //adjust water level in dam 
    return checkdam();         // check if dam is full or dry or nomal
}

bool Dam :: reduceoutletwater(Outlet &O)
{
    Water sub(damwater.pH,O.outletvolume);
    damwater-=sub;                      // calling overloaded operator 
    current_water_level = damwater.volume/(depth.area); //adjust water level in dam
    return checkdam();
}

void Dam::adddepth(int d) 
{
    current_water_level -= d;
    depth + d;                  //calling a overloaded opeartor depth is a objects and d is a integer
}

void Dam::Addoutlet() 
{
    int max_outflowrate;
    cout << "Enter max outflow rate for new outlet: ";
    cin >> max_outflowrate;
    Outlet temp(O.size(), max_outflowrate, 0);
    O.push_back(temp);
}

void Dam::Addinlet() 
{
    int x, y, inflowrate;
    cout << "Enter location of new inlet in depth coordinates: ";
    cin >> x >> y;
    cout << "Enter inflow rate: ";
    cin >> inflowrate;
    Inlet temp(I.size(), x, y);
    I.push_back(temp);
}


void Dam :: simulate(int nsec)
{
    bool st = true;
    for(int j=0; j<nsec; j++)
    {
        for(int i=0; i < I.size(); i++ )
        {
            if(I[i].inflowrate > 0 && addinletwater(I[i]))
                depth.updatedepth(I[i].inlocation[0],I[i].inlocation[1]);
            else
                break;
        }

        for(int i=0; i < O.size(); i++ )
        {
            if(O[i].outletvolume > 0 && reduceoutletwater(O[i]))
                depth.updatedepth(i,float(O.size()));                
            else
                break;
        }
        current_water_level = float(damwater.volume)/depth.area;
    }
    cout << "\nsimulated for " << nsec << " seconds";
}


void Dam :: autopilot()
{
    cout << "Dam on Auto pilot" << endl;
    int totalinflowrate=0;;
    for(int i=0; i< I.size(); i++)
    {
        totalinflowrate+=I[i].inflowrate;
    }
    if(totalinflowrate > O.size()*O[0].max_outflowrate)
    {
        for(int i=0; i<O.size(); i++)
            O[i].operate(100);
        int n=(depth.area*depth.maxdepth - damwater.volume)/(totalinflowrate-O.size()*O[0].max_outflowrate);
        cout << "!!!WARNING!!!\nAll outlets opened at 0 seconds but still Dam may broke at " << n << " seconds"<<endl; 
    }
    else
    {
        int peroutlet = int((float(totalinflowrate)/((O.size())*O[0].max_outflowrate))*100);
        cout << " All outlets status changed to "<< peroutlet << " percent open" <<endl;
        for(int i=0; i<O.size(); i++)
           O[i].operate(peroutlet);
    }
    cout << "Dam returned to manual control" << endl;
}

bool Dam :: checkdam()
{
    if(current_water_level >= depth.maxdepth-1)
    {
        cout << "\nDam full !!!!!\nOpening all outlets"<<endl;
        current_water_level-=1;
        for(int i=0; i<O.size();i++)
            O[i].operate(90);
        return false;
    }
    if(current_water_level == 0)
    {
        cout << "Dam is dry\nClosing all outlets" << endl;
        for(int i=0; i<O.size();i++)
            O[i].operate(0);
        return false;
    }
return true;
}
