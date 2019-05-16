#include "./headers/BelZhabODE.h"
#include "./headers/DropListWrap.h"
#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QLabel>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget *wgt = new QWidget();
    wgt->setWindowTitle("Bautin BZ reaction");

    // Creating basic widgets
    QLabel          *lblA           = new QLabel("Parameter A:");
    QLineEdit       *edA            = new QLineEdit();
    QLabel          *lblB           = new QLabel("Parameter B:");
    QLineEdit       *edB            = new QLineEdit();
    QLabel          *lblC           = new QLabel("Parameter C:");
    QLineEdit       *edC            = new QLineEdit();
    QLabel          *lbl_eps        = new QLabel("Perturbation:");
    QLineEdit       *ed_eps         = new QLineEdit();
    QLabel          *lbl_fin        = new QLabel("Terminal time:");
    QLineEdit       *ed_fin         = new QLineEdit();
    DropListWrap    *init           = new DropListWrap();
    QPushButton     *info           = new QPushButton("Plot");
    QPushButton     *solve          = new QPushButton("Solve");

    // Validator binding
    QDoubleValidator *chkRange  = new QDoubleValidator();
    chkRange->setBottom(0.);
    chkRange->setNotation(QDoubleValidator::StandardNotation);

    edA->setValidator(chkRange);
    edB->setValidator(chkRange);
    edC->setValidator(chkRange);
    ed_eps->setValidator(chkRange);
    ed_fin->setValidator(chkRange);

    // Creating layout
    QFormLayout *layout = new QFormLayout;
    layout->addRow(lblA, edA);
    layout->addRow(lblB, edB);
    layout->addRow(lblC, edC);
    layout->addRow(lbl_eps, ed_eps);
    layout->addRow(lbl_fin, ed_fin);
    layout->addRow(init->strg);
    layout->addRow(solve, info);

    wgt->setLayout(layout);
    wgt->show();

    BelZhabODE *curve = new BelZhabODE;

    // Bindings
    QObject::connect(   edA,    SIGNAL(textEdited(const QString)),
                        curve,    SLOT(set_A(const QString))    );

    QObject::connect(   edA,    SIGNAL(editingFinished()),
                        curve,    SLOT(check_A())               );

    QObject::connect(   edA,    SIGNAL(editingFinished()),
                        init,     SLOT(clear())                 );

    QObject::connect(   edA,    SIGNAL(editingFinished()),
                        curve,    SLOT(pass_init())             );

    QObject::connect(   edB,    SIGNAL(textEdited(const QString)),
                        curve,    SLOT(set_B(const QString))    );

    QObject::connect(   edB,    SIGNAL(editingFinished()),
                        curve,    SLOT(check_B())               );

    QObject::connect(   edB,    SIGNAL(editingFinished()),
                        init,     SLOT(clear())                 );

    QObject::connect(   edB,    SIGNAL(editingFinished()),
                        curve,    SLOT(pass_init())             );

    QObject::connect(   edC,    SIGNAL(textEdited(const QString)),
                        curve,    SLOT(set_C(const QString))    );

    QObject::connect(   edC,    SIGNAL(editingFinished()),
                        curve,    SLOT(check_C())               );

    QObject::connect(   edC,    SIGNAL(editingFinished()),
                        init,     SLOT(clear())                 );

    QObject::connect(   edC,    SIGNAL(editingFinished()),
                        curve,    SLOT(pass_init())             );

    QObject::connect(   ed_eps, SIGNAL(textEdited(const QString)),
                        curve,    SLOT(set_eps(const QString))  );

    QObject::connect(   ed_eps, SIGNAL(editingFinished()),
                        curve,    SLOT(check_eps())             );

    QObject::connect(   ed_fin, SIGNAL(textEdited(const QString)),
                        curve,    SLOT(set_fin(const QString))  );

    QObject::connect(   ed_fin, SIGNAL(editingFinished()),
                        curve,    SLOT(check_fin())             );

    QObject::connect(   info,   SIGNAL(clicked()),
                        curve,    SLOT(plot())                  );

    QObject::connect(   solve,  SIGNAL(clicked()),
                        curve,    SLOT(solve())                 );

    QObject::connect(   curve,  SIGNAL(chngInit(const QString)),
                        init,     SLOT(add(const QString))      );

    QObject::connect(   init->strg, SIGNAL(activated(int)),
                        curve,        SLOT(set_init(int))       );
    return app.exec();
}
