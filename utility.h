#ifndef Utility_H
#define Utility_H


#include <QFile>

#include <QDebug>
#include <QVector>
#include <QFileInfo>

#include <random>

#include <stdlib.h>
#include <stdio.h>

class Utility
{
public:

    Utility();
    ~Utility();

    double Gaussian(double x,double ave,double sigma);
    int argmax(QVector< double>,int *num);
    double drnd();
    double randGaussian( double mu, double sigma );
    void save2(QVector< QVector<double> > ary, QString filename, bool flag=false);
    double Uniform( void );

private:


};

#endif // Utility_H
