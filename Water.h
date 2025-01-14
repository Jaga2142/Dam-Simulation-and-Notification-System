class Water
{
    public:
        float pH;
        int volume;
        Water(float=7,int=0);
        // no destructor drequired as all members are statically allocated
        void operator += (const Water&);     // adds two volumes of water and gives resultant pH
        void operator -= (const Water&);     // reduce quantity of water
        float validatepH(float)const;
};
