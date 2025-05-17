#include <QCoreApplication>
#include <QtGlobal>
#include "utility.h"
#include "bibinference.h"


#define OMEGA 0.09

Utility *util;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    util=new Utility;

    int TMAX=20000;
    int TT=10000;

    double beta=0.05;
    int hsize=51;
    BIBinference *bib=new BIBinference(hsize);
    bib->isInverseBayesianUpdate(true);
    bib->setBeta(beta);



    double mu=-0.5*RANGE+util->drnd()*RANGE;
    double data=0.0;

    QVector<QVector<double> > timeseries;
    timeseries.clear();


    for(int t=0;t<=TMAX;t++)
    {

        if(util->drnd()<0.001)
        {
            mu=(util->drnd()-0.5)*RANGE;
        }


        data=util->randGaussian(mu,OMEGA);

        bib->inference(data);

        if(t>TMAX-TT)
        {
            QVector<double> tmp1;
            tmp1.clear();
            tmp1.append(mu);
            tmp1.append(data);
            tmp1.append(bib->estimate());
            tmp1.append(bib->phi());
            tmp1.append(bib->sigma());
            tmp1.append(bib->alpha());
            tmp1.append(bib->maxH());
            tmp1.append(bib->beta());
            tmp1.append(bib->isReset());
            tmp1.append(bib->isActive());
            timeseries.append(tmp1);

        }

    } //t


    util->save2(timeseries,"estimates.csv");

    qDebug()<<"End";

    return a.exec();
}

