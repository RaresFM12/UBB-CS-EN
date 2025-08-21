QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chef.cpp \
    formgraphic.cpp \
    main.cpp \
    mainwindow.cpp \
    observer.cpp \
    recipe.cpp \
    repository.cpp \
    service.cpp \
    subject.cpp

HEADERS += \
    chef.h \
    formgraphic.h \
    mainwindow.h \
    observer.h \
    recipe.h \
    repository.h \
    service.h \
    subject.h

FORMS += \
    formgraphic.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    chefs.txt \
    recipes.txt
