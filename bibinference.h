#ifndef BIBINFERENCE_H
#define BIBINFERENCE_H



#define BETA 0.1 //忘却率

#define NUMBER_H 51
#define RANGE 5.0
#define INITSIGMA 1.0

#include "utility.h"


class BIBinference
{
public:
    BIBinference();
    BIBinference(int);

    void inference(double d);
    double estimate();

    double sigma();
    double phi();
    double alpha();
    double beta();

    void setBeta(double);
    void isInverseBayesianUpdate(bool);

    bool isActive();

    int maxH();

    bool isReset();

private:
    Utility *util;

    void initialize();

    QVector<double> m_ph;

    int m_premaxh;

    double m_beta;
    bool m_isActive;
    double m_data;
    double m_theta;
    double m_phi;
    bool m_isInverseBayesianUpdate;
    double m_alpha;
    QVector<double> m_mu;


    int m_maxh;

    int m_hsize;

    bool m_isReset;


    double m_sigma;

    int calcMaxH(int *num);



};

#endif // BIBINFERENCE_H
