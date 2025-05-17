#include "bibinference.h"

BIBinference::BIBinference()
{
    m_hsize=NUMBER_H;
    m_isInverseBayesianUpdate=false;
    initialize();
}

BIBinference::BIBinference(int hsize)
{ 
    m_hsize=hsize;
    m_isInverseBayesianUpdate=false;
    initialize();
}

void BIBinference::setBeta(double beta)
{
    m_beta=beta;
}


double BIBinference::sigma()
{
    return m_sigma;
}
double BIBinference::phi()
{
    return m_phi;
}



double BIBinference::alpha()
{
    return m_alpha;
}

bool BIBinference::isActive()
{
    return m_isActive;
}


int BIBinference::maxH()
{
    return m_maxh;
}


double BIBinference::beta()
{
    return m_beta;
}


bool BIBinference::isReset()
{
    return m_isReset;
}

void BIBinference::isInverseBayesianUpdate(bool flag)
{
    m_isInverseBayesianUpdate=flag;
}

void BIBinference::initialize()
{
    util=new Utility;

    m_isActive=false;

    m_isReset=false;
    m_beta=BETA;
    m_theta=0.0;

    m_sigma=INITSIGMA;
    m_phi=m_sigma;


    m_data=0.0;

    m_mu.resize(m_hsize);

    double delta=RANGE/(double)(m_hsize-1);

    for(int i=0;i<m_hsize;i++)
    {
        m_mu[i]=-0.5*RANGE+(double)i*delta;
    }

    m_ph.resize(m_hsize);
    for(int i=0;i<m_ph.size();i++)
    {
        m_ph[i]=util->Gaussian(m_mu[i],m_theta,m_phi);
    }

    int num=1;
    m_maxh=calcMaxH(&num);
    m_premaxh=m_maxh;

    m_alpha=m_phi/(m_phi+(1.0-m_beta)*m_sigma);
}

double BIBinference::estimate()
{
    return m_theta;
}

int BIBinference::calcMaxH(int *num)
{
    *num=1;
    return util->argmax(m_ph,num);
}

void BIBinference::inference(double d)
{

    for(int i=0;i<m_hsize;i++)
    {
        m_ph[i]=util->Gaussian(m_mu[i],m_theta,m_phi);
    }
    m_premaxh=m_maxh;
    int num=1;
    m_maxh=calcMaxH(&num);


    //reset likelihood
    if(m_premaxh!=m_maxh)
    {
        m_isReset=true;
        m_sigma=INITSIGMA;

    }
    else
    {
        m_isReset=false;
    }

    m_data=d;

    //Bayesian update
    double alpha=m_phi/(m_phi+(1.0-m_beta)*m_sigma);
    double theta=alpha*d+(1.0-alpha)*m_theta;

    double phi=m_phi/((1.0-m_beta)*m_sigma+m_phi)*m_sigma;
    double sigma=m_sigma;

    if(m_isInverseBayesianUpdate)
    {
        //inverse Bayesian update
        sigma=(m_sigma+m_phi)/((1.0-m_beta)*m_sigma+m_phi)*m_sigma;
    }

    m_phi=phi;

    m_theta=theta;
    m_sigma=sigma;
    m_alpha=m_phi/(m_phi+(1.0-m_beta)*m_sigma);

    if(m_alpha>m_beta)
        m_isActive=true;
    else
        m_isActive=false;

}








