#include "../headers/DropListWrap.h"

DropListWrap::DropListWrap() : strg(new QComboBox) {
    strg->addItem("0.0, 0.0");
    return;
}

void DropListWrap::add(const QString str)
{
    strg->addItem(str);
    return;
}

void DropListWrap::clear()
{
    strg->clear();
    strg->addItem("0.0, 0.0");
    return;
}