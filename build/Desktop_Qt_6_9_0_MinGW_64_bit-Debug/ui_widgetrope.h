/********************************************************************************
** Form generated from reading UI file 'widgetrope.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETROPE_H
#define UI_WIDGETROPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetRope
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *gravity;
    QLabel *label_3;
    QDoubleSpinBox *springStiffness;
    QLabel *label_6;
    QDoubleSpinBox *springDamping;
    QLabel *label_2;
    QDoubleSpinBox *ropeLength;
    QLabel *label_4;
    QSpinBox *numParticles;
    QLabel *label_5;
    QDoubleSpinBox *particleScale;
    QCheckBox *checkCollisions;
    QCheckBox *anchoredEnd;
    QPushButton *btnUpdate;
    QLabel *label_7;
    QComboBox *startConfig;
    QCheckBox *showParticles;
    QLabel *label_8;
    QComboBox *integrators;

    void setupUi(QWidget *WidgetRope)
    {
        if (WidgetRope->objectName().isEmpty())
            WidgetRope->setObjectName("WidgetRope");
        WidgetRope->resize(270, 436);
        formLayout = new QFormLayout(WidgetRope);
        formLayout->setObjectName("formLayout");
        label = new QLabel(WidgetRope);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        gravity = new QDoubleSpinBox(WidgetRope);
        gravity->setObjectName("gravity");
        gravity->setMaximum(100.000000000000000);
        gravity->setSingleStep(1.000000000000000);
        gravity->setValue(9.810000000000000);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, gravity);

        label_3 = new QLabel(WidgetRope);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_3);

        springStiffness = new QDoubleSpinBox(WidgetRope);
        springStiffness->setObjectName("springStiffness");
        springStiffness->setMaximum(1000.000000000000000);
        springStiffness->setSingleStep(10.000000000000000);
        springStiffness->setValue(200.000000000000000);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, springStiffness);

        label_6 = new QLabel(WidgetRope);
        label_6->setObjectName("label_6");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_6);

        springDamping = new QDoubleSpinBox(WidgetRope);
        springDamping->setObjectName("springDamping");
        springDamping->setMaximum(1.000000000000000);
        springDamping->setSingleStep(0.100000000000000);
        springDamping->setValue(0.500000000000000);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, springDamping);

        label_2 = new QLabel(WidgetRope);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_2);

        ropeLength = new QDoubleSpinBox(WidgetRope);
        ropeLength->setObjectName("ropeLength");
        ropeLength->setMaximum(200.000000000000000);
        ropeLength->setSingleStep(1.000000000000000);
        ropeLength->setValue(100.000000000000000);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, ropeLength);

        label_4 = new QLabel(WidgetRope);
        label_4->setObjectName("label_4");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_4);

        numParticles = new QSpinBox(WidgetRope);
        numParticles->setObjectName("numParticles");
        numParticles->setMinimum(2);
        numParticles->setMaximum(1000);
        numParticles->setSingleStep(10);
        numParticles->setValue(10);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, numParticles);

        label_5 = new QLabel(WidgetRope);
        label_5->setObjectName("label_5");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_5);

        particleScale = new QDoubleSpinBox(WidgetRope);
        particleScale->setObjectName("particleScale");
        particleScale->setMaximum(100.000000000000000);
        particleScale->setSingleStep(0.100000000000000);
        particleScale->setValue(1.000000000000000);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, particleScale);

        checkCollisions = new QCheckBox(WidgetRope);
        checkCollisions->setObjectName("checkCollisions");
        checkCollisions->setChecked(true);

        formLayout->setWidget(8, QFormLayout::ItemRole::SpanningRole, checkCollisions);

        anchoredEnd = new QCheckBox(WidgetRope);
        anchoredEnd->setObjectName("anchoredEnd");
        anchoredEnd->setChecked(true);

        formLayout->setWidget(9, QFormLayout::ItemRole::SpanningRole, anchoredEnd);

        btnUpdate = new QPushButton(WidgetRope);
        btnUpdate->setObjectName("btnUpdate");

        formLayout->setWidget(11, QFormLayout::ItemRole::SpanningRole, btnUpdate);

        label_7 = new QLabel(WidgetRope);
        label_7->setObjectName("label_7");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, label_7);

        startConfig = new QComboBox(WidgetRope);
        startConfig->addItem(QString());
        startConfig->addItem(QString());
        startConfig->addItem(QString());
        startConfig->setObjectName("startConfig");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, startConfig);

        showParticles = new QCheckBox(WidgetRope);
        showParticles->setObjectName("showParticles");
        showParticles->setChecked(true);

        formLayout->setWidget(10, QFormLayout::ItemRole::SpanningRole, showParticles);

        label_8 = new QLabel(WidgetRope);
        label_8->setObjectName("label_8");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, label_8);

        integrators = new QComboBox(WidgetRope);
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->setObjectName("integrators");

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, integrators);


        retranslateUi(WidgetRope);

        QMetaObject::connectSlotsByName(WidgetRope);
    } // setupUi

    void retranslateUi(QWidget *WidgetRope)
    {
        WidgetRope->setWindowTitle(QCoreApplication::translate("WidgetRope", "Form", nullptr));
        label->setText(QCoreApplication::translate("WidgetRope", "Gravity", nullptr));
        label_3->setText(QCoreApplication::translate("WidgetRope", "Spring stiffness", nullptr));
        label_6->setText(QCoreApplication::translate("WidgetRope", "Spring damp", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetRope", "Rope length", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetRope", "Num particles", nullptr));
        label_5->setText(QCoreApplication::translate("WidgetRope", "Particle radius", nullptr));
        checkCollisions->setText(QCoreApplication::translate("WidgetRope", "Check collisions", nullptr));
        anchoredEnd->setText(QCoreApplication::translate("WidgetRope", "Anchor rope end", nullptr));
        btnUpdate->setText(QCoreApplication::translate("WidgetRope", "Update", nullptr));
        label_7->setText(QCoreApplication::translate("WidgetRope", "Start config", nullptr));
        startConfig->setItemText(0, QCoreApplication::translate("WidgetRope", "Vertical", nullptr));
        startConfig->setItemText(1, QCoreApplication::translate("WidgetRope", "Horizontal", nullptr));
        startConfig->setItemText(2, QCoreApplication::translate("WidgetRope", "Helix", nullptr));

        showParticles->setText(QCoreApplication::translate("WidgetRope", "Show particles", nullptr));
        label_8->setText(QCoreApplication::translate("WidgetRope", "Integrator", nullptr));
        integrators->setItemText(0, QCoreApplication::translate("WidgetRope", "Euler", nullptr));
        integrators->setItemText(1, QCoreApplication::translate("WidgetRope", "Symplectic Euler", nullptr));
        integrators->setItemText(2, QCoreApplication::translate("WidgetRope", "Midpoint", nullptr));
        integrators->setItemText(3, QCoreApplication::translate("WidgetRope", "RK2", nullptr));
        integrators->setItemText(4, QCoreApplication::translate("WidgetRope", "RK4", nullptr));
        integrators->setItemText(5, QCoreApplication::translate("WidgetRope", "Verlet", nullptr));

    } // retranslateUi

};

namespace Ui {
    class WidgetRope: public Ui_WidgetRope {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETROPE_H
