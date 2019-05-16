#pragma once
#include <QComboBox>
#include <QString>

class DropListWrap : public QObject
{
    Q_OBJECT

public:
    QComboBox *strg;
    DropListWrap();

public slots:
    void clear();
    void add(const QString);
};
