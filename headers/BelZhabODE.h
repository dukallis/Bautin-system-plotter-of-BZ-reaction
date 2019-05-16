#pragma once
#include <QtCore>
#include <QObject>
#include <QString>

class BelZhabODE : public QObject {
    Q_OBJECT

private:
    QString A,B,C;                  // Parameters for dynamical system (strings)
    QString eps;                    // Initial point pertirbation
    QString fin;                    // Terminal time
    bool dataChng;                  // Flag to check if data above have changed
    const double h_step;            // fixed step size for explicit Runge-Kutta method

    // Numeric information
    QVector<double> x, y;
    int init_ind;
    QVector<double> x_init, y_init; // Initial points
    double numA, numB, numC;
    double num_eps, num_fin;
    QVector<double> F(const QVector<double>&) const;
    inline double dxdt(const double x, const double y) const {
        return numA*x + numB*y - x*(x*x + y*y);
    };
    inline double dydt(const double x, const double y) const {
        return -numA*x + numC*y - y*(x*x + y*y);
    };
    void check(QString&, const QString&, double&);

public:
    BelZhabODE();

public slots:
    inline void set_A(const QString str) { A = str; };
    void check_A();
    inline void set_B(const QString str) { B = str; };
    void check_B();
    inline void set_C(const QString str) { C = str; };
    void check_C();
    inline void set_eps(const QString str) { eps = str; };
    void check_eps();
    inline void set_fin(const QString str) { fin = str; };
    void check_fin();
    void pass_init();
    void set_init(int);
    void plot();
    void solve();

signals:
    void chngInit(const QString);
};
