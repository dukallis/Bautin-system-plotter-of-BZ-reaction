#include "../headers/BelZhabODE.h"
#include "../qcustomplot/qcustomplot.h"
#include <cmath>

BelZhabODE::BelZhabODE(): QObject()
                        , A(""), B(""), C("")
                        , eps(""), fin("")
                        , dataChng(false)
                        , h_step(0.05)
                        , x({0.}), y({0.})
                        , init_ind(0), x_init({0.}), y_init({0.})
                        , numA(0.), numB(0.), numC(0.)
                        , num_eps(0.), num_fin(0.) {}

void BelZhabODE::check(QString& prev, const QString& cur, double& num)
{
    if (cur != prev) {
        dataChng = true;
        prev = cur;
        num = cur.toDouble();
    }
    return;
}

void BelZhabODE::check_A() {
    static QString pA = "";
    check(pA, A, numA);
    return;
}

void BelZhabODE::check_B() {
    static QString pB = "";
    check(pB, B, numB);
    return;
}

void BelZhabODE::check_C() {
    static QString pC = "";
    check(pC, C, numC);
    return;
}

void BelZhabODE::check_eps() {
    static QString p_eps = "";
    check(p_eps, eps, num_eps);
    return;
}

void BelZhabODE::check_fin() {
    static QString p_fin = "";
    check(p_fin, fin, num_fin);
    return;
}


void BelZhabODE::pass_init() {
    // Starting new initial points vector
    x_init.clear();
    y_init.clear();
    x_init.push_back(0.);
    y_init.push_back(0.);

    double discr = (numA - numC)*(numA - numC) - 4*numB*numA;

    if (discr < 0.0 || qFuzzyCompare(1. + numB, 1. + 0.0))
        return;

    double k_1 = ( (numC - numA) + sqrt(discr) ) / (2*numB);
    double k_2 = ( (numC - numA) - sqrt(discr) ) / (2*numB);

    double numer_1 = numA + numB*k_1;
    double denom_1 = 1. + k_1*k_1;

    double numer_2 = numA + numB*k_2;
    double denom_2 = 1. + k_2*k_2;

    double x_11 = sqrt(numer_1 / denom_1);
    double y_11 = x_11*k_1;
    double x_12 = -x_11;
    double y_12 = -y_11;

    double x_21 = sqrt(numer_2 / denom_2);
    double y_21 = x_21*k_2;
    double x_22 = -x_21;
    double y_22 = -y_21;

    x_init.push_back(x_11);
    y_init.push_back(y_11);
    x_init.push_back(x_12);
    y_init.push_back(y_12);
    x_init.push_back(x_21);
    y_init.push_back(y_21);
    x_init.push_back(x_22);
    y_init.push_back(y_22);

    QString str = "";
    emit chngInit(str.setNum(x_11, 'g', 5) + ", " + str.setNum(y_11, 'g', 5));
    emit chngInit(str.setNum(x_12, 'g', 5) + ", " + str.setNum(y_12, 'g', 5));
    emit chngInit(str.setNum(x_21, 'g', 5) + ", " + str.setNum(y_21, 'g', 5));
    emit chngInit(str.setNum(x_22, 'g', 5) + ", " + str.setNum(y_22, 'g', 5));
    return;
}

void BelZhabODE::set_init(int i) {
    if (i != init_ind) {
        init_ind = i;
        dataChng = true;
    }
    return;
}

template<> QVector<double>
QVector<double>::operator+(const QVector<double>& v1) const
{
    QVector<double> res;
    for (QVector<double>::size_type i = 0; i < v1.size(); ++i)
        res.push_back((*this)[i] + v1[i]);
    return res;
}

static QVector<double> operator*(
                                    const double num,
                                    const QVector<double>& vec
                                )
{
    QVector<double> res;
    for (QVector<double>::size_type i = 0; i < vec.size(); ++i)
        res.push_back(num*vec[i]);
    return res;
}

QVector<double> BelZhabODE::F(const QVector<double>& vec) const
{
    QVector<double> res;
    res.push_back(dxdt(vec[0], vec[1]));
    res.push_back(dydt(vec[0], vec[1]));
    return res;
}

void BelZhabODE::solve() {
    if (dataChng == false)
        return;

    // Start new solution
    x.clear();
    y.clear();

    x.push_back(x_init[init_ind] + num_eps);
    y.push_back(y_init[init_ind] + num_eps);

    size_t nstep = (size_t) (num_fin / h_step);
    for (size_t i = 1; i <= nstep; ++i) {
        QVector<double> vec = {x[i-1], y[i-1]};
        QVector<double> k1, k2, k3, k4;
        k1 = F(vec);
        k2 = F(vec + (h_step/2)*k1);
        k3 = F(vec + (h_step/2)*k2);
        k4 = F(vec + h_step*k3);
        QVector<double> nxt = vec + (h_step/6)*(k1 + 2*k2 + 2*k3 + k4);
        x.push_back(nxt[0]);
        y.push_back(nxt[1]);
    }
    dataChng = false;
    return;
}

void BelZhabODE::plot()
{
    QCustomPlot *customPlot = new QCustomPlot();
    QCPCurve *newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
    newCurve->setData(x, y);
    newCurve->rescaleAxes();
    customPlot->setMinimumSize(100,101);
    customPlot->setInteraction(QCP::iRangeZoom, true);
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->replot();
    customPlot->resize(800,600);
    customPlot->show();
    return;
}
