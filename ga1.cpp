#include<bits/stdc++.h>

#define popsize 2400
#define max_no_of_iter 16384
#define elitismrate 0.10f
#define mutationrate 0.25f
#define genmutat RAND_MAX * mutationrate
#define target std::string("Genetic Algorithm")

using namespace std;
struct genetic{   //structure for the dna
string gene;
unsigned int fit;//specifies the fitness of the gene
};
typedef vector<genetic> chromosome;

void population(chromosome &presentgen,chromosome &futuregen)
{
    for(int i=0;i<popsize;i++)
    {
        genetic individual;
        individual.gene.erase();
        individual.fit=0;
        for(int j=0;j<target.size();j++)
        {
            individual.gene+=(rand()%90)+32;//assigning random characters to each gene character
        }
        presentgen.push_back(individual);
    }
    futuregen.resize(popsize);//future generation will also be having the same size as present generation
}

void fitnessfunction(chromosome &presentgen)
{
    string tar=target;
    unsigned int score;
    for(int i=0;i<popsize;i++)
    {
        score=0;
        for(int j=0;j<target.size();j++)
        {
            if(presentgen[i].gene[j]==tar[j])
            {
                score++;// my fitness function works on the point that how many characters of respective gene are similar to the wanted gene
            }
        }//fitness functions could be different
        presentgen[i].fit=score;
    }
}

bool mostfit(genetic a, genetic b)
{
    return(a.fit>b.fit);
}
// the below and above functions both helps to sort the population on basis of fitness in descending order so as to access the best fit of that population easily
void sort_by_fit(chromosome &presentgen)
{
    sort(presentgen.begin(),presentgen.end(),mostfit);
}

void elitism(chromosome &presentgen,chromosome &futuregen,int elitismper)
{//elitism is the process of how many population of current generation can remain in the future generation also
    for(int i=0;i<elitismper;i++)
    {
        futuregen[i].gene=presentgen[i].gene;
        futuregen[i].fit=presentgen[i].fit;
    }//usually the population which remains will be the fit among that population
}

void mutate(genetic &mutatedgene)//Mutation is a genetic operator used to maintain genetic diversity from one generation of a population of genetic algorithm chromosomes to the next
{
    int posformuta=rand()%target.size();
    int newchar=(rand()%90)+32;
    mutatedgene.gene[posformuta]=((mutatedgene.gene[posformuta]+newchar)%122);
}

void crossover(chromosome &presentgen,chromosome &futuregen)//crossover is a genetic operator used to vary the programming of a chromosome or chromosomes from one generation to the next
{
    int elitismper=popsize*elitismrate;//calculating percentage of elitism
    int gene1,gene2,breakpoint;
    elitism(presentgen,futuregen,elitismper);//calling function to retain that better percentage population
    for(int i=elitismper;i<popsize;i++)
    {
        gene1=rand()%(popsize/2);
        gene2=rand()%(popsize/2);
        breakpoint=rand()%target.size();
        futuregen[i].gene=presentgen[gene1].gene.substr(0,breakpoint)+presentgen[gene2].gene.substr(breakpoint,elitismper-breakpoint);
        if(rand()<genmutat)
        {
            mutate(futuregen[i]);
        }
    }
}

void swap_pres_futu(chromosome *&presentgen,chromosome *&futuregen)// swapping present gen and future gen so as to make use of new population in the next generation
{
    chromosome *temp=presentgen;
    presentgen=futuregen;
    futuregen=temp;
}

void bestfit(chromosome &best)
{
    cout<<"Best Fit : "<<best[0].gene<<" with the fitness of -> "<<best[0].fit;//sort function helped this procedure
}

int main()
{
    srand(unsigned(time(NULL)));
    chromosome pop1,pop2;
    chromosome *presentgen,*futuregen;
    population(pop1,pop2);
    presentgen=&pop1;
    futuregen=&pop2;
    for(int i=0;i<max_no_of_iter;i++)
    {
        fitnessfunction(*presentgen);
        sort_by_fit(*presentgen);
        cout<<endl<<"Generation number : "<<i<<endl;
        bestfit(*presentgen);
        /*for(int j=0;j<popsize;j++)//to see whole population of each generation
        {
            cout<<" Gene : "<<j<<" : "<<(*presentgen)[j].gene<<" with the fitness of -> "<<(*presentgen)[j].fit<<endl;
        }*/
        if ((*presentgen)[0].gene==target)//if target solution is equal to best solution of this generation
        {
            break;
        }
        crossover(*presentgen,*futuregen);
        swap_pres_futu(presentgen,futuregen);
    }
    return 0;
}
