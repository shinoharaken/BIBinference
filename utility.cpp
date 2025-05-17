#include "Utility.h"
using namespace std;
std::random_device seed_gen;
std::mt19937 engine(seed_gen());
std::uniform_real_distribution<> uniformdist(0.0, 1.0);
std::normal_distribution<> normaldist(0.0, 1.0);
#define M__PI 3.14159265358979323846//3.14159265358979
Utility::Utility()
{
    std::srand( time(NULL) );
}

Utility::~Utility()
{


}

double Utility::Gaussian(double x,double ave,double sigma)
{
    double val=0.0;

    val=1.0/sqrt(2.0*M_PI*sigma)*exp(-(x-ave)*(x-ave)/(2.0*sigma));
    return val;

}

double Utility::randGaussian( double mu, double omega ){

    double z=sqrt( -2.0*log(Uniform()) ) * sin( 2.0*M_PI*Uniform() );

    return mu + sqrt(omega)*z;
}

double Utility::Uniform( void ){
    return ((double)rand()+1.0)/((double)RAND_MAX+2.0);
}

int Utility::argmax(QVector< double> data,int *num)
{

    *num=1;
    int index=0;
    if(data.size()==0)
        return index;

    QVector<int> tmp;
    tmp.clear();

    double max=data.at(0);
    tmp.append(0);
    for(int i=1;i<data.size();i++)
    {
        if(max<data.at(i))
        {
            tmp.clear();
            tmp.append(i);
            max=data.at(i);
        }
        else if(max==data.at(i))
        {
            tmp.append(i);

        }
    }

    index=tmp.at((int)((double)tmp.size()*drnd()));
    *num=tmp.size();

    return index;

}

void Utility::save2(QVector< QVector<double> > ary, QString filename,bool flag)
{
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Cannot open the output file.";
        return;
    }
    std::string sep=" ";
    QFileInfo info(filename);
    if(info.suffix()=="csv")
        sep=",";

    QTextStream out(&file);
    std::stringstream ss;

    if(!flag)
    {
        for(int i=0;i<ary.size();i++)
        {
            for(int j=0;j<ary[i].size();j++)
            {
                if(j>0)
                    ss<<sep<<ary[i][j];
                else
                    ss<<ary[i][j];
            }
            ss<<std::endl;

        }
    }
    else
    {

        for(int i=0;i<ary.size();i++)
        {
            for(int j=0;j<ary[i].size();j++)
            {
                if(j>0)
                    ss<<sep<<ary[i][j];
                else
                    ss<<ary[i][j];
            }
            ss<<std::endl;

        }

    }

    out << ss.str().c_str();
    file.close();

}

double Utility::drnd()
{
    return uniformdist(engine);
}


