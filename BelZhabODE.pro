TEMPLATE = app
QT +=   core \
        widgets \
        printsupport \
        gui
SOURCES +=  ./source/BelZhabODE.cpp \
            ./source/DropListWrap.cpp \
            ./qcustomplot/qcustomplot.cpp \
            ./main.cpp
HEADERS +=  ./headers/BelZhabODE.h \
            ./headers/DropListWrap.h \
            ./qcustomplot/qcustomplot.h
TARGET = ./build/Solver