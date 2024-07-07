#include <bits/stdc++.h>
using namespace std;

random_device rd;
mt19937 gen(rd());

long long int RandomNum(long long int st,long long int end)
{
    uniform_int_distribution<> dis(st, end);
    long long int number = dis(gen);
    return number;
}
//we can use uniform real dist and calc probability by generating random numbers from 0 to 1

bool probability(double prob)
{
    long long hehe = prob * 100000;
    long long int huhu = RandomNum(1,100000);
    return (huhu <= hehe);
}

struct Individual
{
    uint16_t firstpart;
    uint16_t secondpart;
};

Individual SetIndividual()
{
    Individual baccha;
    baccha.firstpart = RandomNum(0,(1<<16 - 1));
    baccha.secondpart = RandomNum(0,(1<<16 - 1));
    return baccha;
}

Individual PaidaKaro(Individual parent1,Individual parent2)
{
    Individual baccha;
    if(RandomNum(0,1))
    {
        baccha.firstpart = parent1.firstpart;
        baccha.secondpart = parent2.secondpart;
    }
    else
    {
        baccha.firstpart = parent2.firstpart;
        baccha.secondpart = parent1.secondpart;
    }
    if(probability(0.0))
    {
        //third implementation optimised i didnt realise xor can be used to flip bits
        int BitFlip = RandomNum(0, 31);  // Get a bit position to flip (0-based index)
        uint32_t FullNumber = (static_cast<uint32_t>(baccha.firstpart) << 16) | baccha.secondpart;
        // Flip the bit using XOR
        FullNumber ^= (1u << BitFlip);
        // Split FullNumber back into firstpart and secondpart
        baccha.firstpart = static_cast<uint16_t>(FullNumber >> 16);
        baccha.secondpart = static_cast<uint16_t>(FullNumber & 0b00000000000000001111111111111111); 


        //second implementation "BITFLIP"
        // int BitFlip = RandomNum(1,32) - 1;
        // uint32_t FullNumber = baccha.firstpart *1ll *pow(2,16) + baccha.secondpart*1ll;
        // uint32_t FullNumberCopy = FullNumber;
        // uint8_t bit= (FullNumberCopy >> BitFlip) & 1;
        // if(bit)
        // {
        //     FullNumber = FullNumber - pow(2,BitFlip);  
        // }
        // else
        // {
        //     FullNumber = FullNumber + pow(2,BitFlip);
        // }
        // baccha.firstpart = static_cast<uint16_t>(FullNumber >> 16);
        // baccha.secondpart = static_cast<uint16_t>((FullNumber << 16) >> 16)



        //first implementation of mutation was to or with random 2 ke powers 
        // uint32_t mutation = 1u << RandomNum(0,31);
        // uint32_t* pmutation = &mutation;
        // baccha.firstpart = *((uint16_t*) pmutation) | baccha.firstpart;
        // baccha.secondpart = *(((uint16_t*) pmutation) + 1) | baccha.secondpart;
    }    
    return baccha;
}

// void PrintPopulation(Individual* Population,uint32_t size)
// {
//     for(int i = 0;i<size;i++)
//     {
//         cout << "First Part "<<Population[i].firstpart<<" Second Part "<<Population[i].secondpart << " Total : "  <<static_cast<int>(Population[i].firstpart*1ll*pow(2,16) + Population[i].secondpart*1ll)<<endl;
//     }
// }

void PrintPopulation(Individual* Population, uint32_t size)
{
    auto to_binary_string = [](uint16_t num) {
        string binary;
        for (int i = 15; i >= 0; --i) {
            binary += ((num >> i) & 1) ? '1' : '0';
        }
        return binary;
    };

    for (uint32_t i = 0; i < size; ++i)
    {
        cout << "First Part " << to_binary_string(Population[i].firstpart)
             << " Second Part " << to_binary_string(Population[i].secondpart) << endl;
    }
}

Individual* GetNewPopulation(Individual* PrevPopulation,uint32_t size)
{
    uint32_t* ParPopulation = (uint32_t*)(PrevPopulation);
    sort(ParPopulation,ParPopulation+size/*,greater()*/);  
    Individual* NewPopulation = new Individual[size];    
    for (int i = 0;i<size/2;i++)
    {
        int a = i;
        while(a == i)
        {
            a = RandomNum(0,size/2 - 1);
        }
        NewPopulation[i] = PaidaKaro(*((Individual*)ParPopulation+i),*((Individual *)ParPopulation+a));
        int b = i;
        while((b == i) or (a == b))
        {
            b = RandomNum(0,size/2 - 1);
        }
        NewPopulation[(size/2) + i] = PaidaKaro(*((Individual*)ParPopulation+i),*((Individual *)ParPopulation+b));
    }
    delete [] ParPopulation;
    return NewPopulation;
}

int main()
{
    //even
    int StartingPopulation = 1000;
    Individual* Population = new Individual[StartingPopulation];
    int generation_number = 0; 
    for(int i = 0;i<StartingPopulation;i++)
    {
        Population[i] = SetIndividual();
    }
    cout << "Generation " <<generation_number<<endl;
    PrintPopulation(Population,StartingPopulation);
    int t;
    cout << "Number of generations ";
    cin >> t;

    while(t--)
    {
        cout << endl;
        Population = GetNewPopulation(Population,StartingPopulation);
        generation_number++;
        cout << "Generation " <<generation_number<<endl;        
        PrintPopulation(Population,StartingPopulation);
    }
    delete[] Population;
}