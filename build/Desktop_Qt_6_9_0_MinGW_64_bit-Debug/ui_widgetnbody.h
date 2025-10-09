/********************************************************************************
** Form generated from reading UI file 'widgetnbody.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETNBODY_H
#define UI_WIDGETNBODY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetNBody
{
public:
    QFormLayout *formLayout;
    QComboBox *integrator;
    QLabel *label_3;
    QComboBox *bodiesLayout;
    QLabel *label;
    QSpinBox *numBodies;
    QLabel *label_2;
    QDoubleSpinBox *massRange;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *smoothA;
    QDoubleSpinBox *smoothB;
    QCheckBox *trajectory;

    void setupUi(QWidget *WidgetNBody)
    {
        if (WidgetNBody->objectName().isEmpty())
            WidgetNBody->setObjectName("WidgetNBody");
        WidgetNBody->resize(211, 453);
        formLayout = new QFormLayout(WidgetNBody);
        formLayout->setObjectName("formLayout");
        integrator = new QComboBox(WidgetNBody);
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->addItem(QString());
        integrator->setObjectName("integrator");

        formLayout->setWidget(0, QFormLayout::ItemRole::SpanningRole, integrator);

        label_3 = new QLabel(WidgetNBody);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_3);

        bodiesLayout = new QComboBox(WidgetNBody);
        bodiesLayout->addItem(QString());
        bodiesLayout->addItem(QString());
        bodiesLayout->addItem(QString());
        bodiesLayout->setObjectName("bodiesLayout");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, bodiesLayout);

        label = new QLabel(WidgetNBody);
        label->setObjectName("label");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label);

        numBodies = new QSpinBox(WidgetNBody);
        numBodies->setObjectName("numBodies");
        numBodies->setMinimum(2);
        numBodies->setMaximum(100);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, numBodies);

        label_2 = new QLabel(WidgetNBody);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_2);

        massRange = new QDoubleSpinBox(WidgetNBody);
        massRange->setObjectName("massRange");
        massRange->setDecimals(1);
        massRange->setMinimum(1.000000000000000);
        massRange->setMaximum(10.000000000000000);
        massRange->setSingleStep(0.100000000000000);
        massRange->setValue(1.000000000000000);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, massRange);

        label_4 = new QLabel(WidgetNBody);
        label_4->setObjectName("label_4");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        smoothA = new QDoubleSpinBox(WidgetNBody);
        smoothA->setObjectName("smoothA");
        smoothA->setDecimals(2);
        smoothA->setMaximum(100.000000000000000);
        smoothA->setValue(2.000000000000000);

        horizontalLayout->addWidget(smoothA);

        smoothB = new QDoubleSpinBox(WidgetNBody);
        smoothB->setObjectName("smoothB");
        smoothB->setDecimals(2);
        smoothB->setMinimum(0.010000000000000);
        smoothB->setMaximum(100.000000000000000);
        smoothB->setValue(10.000000000000000);

        horizontalLayout->addWidget(smoothB);


        formLayout->setLayout(4, QFormLayout::ItemRole::FieldRole, horizontalLayout);

        trajectory = new QCheckBox(WidgetNBody);
        trajectory->setObjectName("trajectory");
        trajectory->setChecked(true);

        formLayout->setWidget(5, QFormLayout::ItemRole::SpanningRole, trajectory);


        retranslateUi(WidgetNBody);

        integrator->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(WidgetNBody);
    } // setupUi

    void retranslateUi(QWidget *WidgetNBody)
    {
        WidgetNBody->setWindowTitle(QCoreApplication::translate("WidgetNBody", "Form", nullptr));
        integrator->setItemText(0, QCoreApplication::translate("WidgetNBody", "Euler", nullptr));
        integrator->setItemText(1, QCoreApplication::translate("WidgetNBody", "Symplectic Euler", nullptr));
        integrator->setItemText(2, QCoreApplication::translate("WidgetNBody", "Midpoint", nullptr));
        integrator->setItemText(3, QCoreApplication::translate("WidgetNBody", "RK2 (Heun)", nullptr));
        integrator->setItemText(4, QCoreApplication::translate("WidgetNBody", "RK4", nullptr));
        integrator->setItemText(5, QCoreApplication::translate("WidgetNBody", "Verlet", nullptr));

        label_3->setText(QCoreApplication::translate("WidgetNBody", "Layout", nullptr));
        bodiesLayout->setItemText(0, QCoreApplication::translate("WidgetNBody", "Circle", nullptr));
        bodiesLayout->setItemText(1, QCoreApplication::translate("WidgetNBody", "Sphere", nullptr));
        bodiesLayout->setItemText(2, QCoreApplication::translate("WidgetNBody", "Cylinder", nullptr));

        label->setText(QCoreApplication::translate("WidgetNBody", "N", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetNBody", "Masses range", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetNBody", "Smoothing", nullptr));
        trajectory->setText(QCoreApplication::translate("WidgetNBody", "Show trajectories", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetNBody: public Ui_WidgetNBody {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETNBODY_H
