/********************************************************************************
** Form generated from reading UI file 'widgetprojectiles.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETPROJECTILES_H
#define UI_WIDGETPROJECTILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetProjectiles
{
public:
    QFormLayout *formLayout;
    QLabel *label_2;
    QDoubleSpinBox *gravity;
    QLabel *label;
    QDoubleSpinBox *height;
    QLabel *label_4;
    QDoubleSpinBox *speed;
    QLabel *label_3;
    QDoubleSpinBox *angle;
    QLabel *label_5;
    QComboBox *solver1;
    QLabel *label_6;
    QComboBox *solver2;
    QCheckBox *trajectory;
    QCheckBox *sameZ;
    QLabel *label_7;
    QHBoxLayout *qlayout2;
    QDoubleSpinBox *klinear;
    QLabel *label_8;
    QHBoxLayout *qlayout1;
    QDoubleSpinBox *kquadratic;

    void setupUi(QWidget *WidgetProjectiles)
    {
        if (WidgetProjectiles->objectName().isEmpty())
            WidgetProjectiles->setObjectName("WidgetProjectiles");
        WidgetProjectiles->resize(262, 453);
        formLayout = new QFormLayout(WidgetProjectiles);
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(WidgetProjectiles);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_2);

        gravity = new QDoubleSpinBox(WidgetProjectiles);
        gravity->setObjectName("gravity");
        gravity->setSingleStep(0.100000000000000);
        gravity->setValue(9.810000000000000);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, gravity);

        label = new QLabel(WidgetProjectiles);
        label->setObjectName("label");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label);

        height = new QDoubleSpinBox(WidgetProjectiles);
        height->setObjectName("height");
        height->setMaximum(100.000000000000000);
        height->setValue(30.000000000000000);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, height);

        label_4 = new QLabel(WidgetProjectiles);
        label_4->setObjectName("label_4");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_4);

        speed = new QDoubleSpinBox(WidgetProjectiles);
        speed->setObjectName("speed");
        speed->setMaximum(50.000000000000000);
        speed->setValue(40.000000000000000);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, speed);

        label_3 = new QLabel(WidgetProjectiles);
        label_3->setObjectName("label_3");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_3);

        angle = new QDoubleSpinBox(WidgetProjectiles);
        angle->setObjectName("angle");
        angle->setMinimum(-90.000000000000000);
        angle->setMaximum(90.000000000000000);
        angle->setValue(45.000000000000000);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, angle);

        label_5 = new QLabel(WidgetProjectiles);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("font-weight:bold;color:darkred"));

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_5);

        solver1 = new QComboBox(WidgetProjectiles);
        solver1->addItem(QString());
        solver1->addItem(QString());
        solver1->addItem(QString());
        solver1->addItem(QString());
        solver1->addItem(QString());
        solver1->addItem(QString());
        solver1->setObjectName("solver1");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, solver1);

        label_6 = new QLabel(WidgetProjectiles);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("font-weight:bold;color:darkblue"));

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_6);

        solver2 = new QComboBox(WidgetProjectiles);
        solver2->addItem(QString());
        solver2->addItem(QString());
        solver2->addItem(QString());
        solver2->addItem(QString());
        solver2->addItem(QString());
        solver2->addItem(QString());
        solver2->setObjectName("solver2");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, solver2);

        trajectory = new QCheckBox(WidgetProjectiles);
        trajectory->setObjectName("trajectory");

        formLayout->setWidget(6, QFormLayout::ItemRole::SpanningRole, trajectory);

        sameZ = new QCheckBox(WidgetProjectiles);
        sameZ->setObjectName("sameZ");

        formLayout->setWidget(7, QFormLayout::ItemRole::SpanningRole, sameZ);

        label_7 = new QLabel(WidgetProjectiles);
        label_7->setObjectName("label_7");

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, label_7);

        qlayout2 = new QHBoxLayout();
        qlayout2->setObjectName("qlayout2");
        klinear = new QDoubleSpinBox(WidgetProjectiles);
        klinear->setObjectName("klinear");
        klinear->setSingleStep(0.100000000000000);

        qlayout2->addWidget(klinear);


        formLayout->setLayout(8, QFormLayout::ItemRole::FieldRole, qlayout2);

        label_8 = new QLabel(WidgetProjectiles);
        label_8->setObjectName("label_8");

        formLayout->setWidget(9, QFormLayout::ItemRole::LabelRole, label_8);

        qlayout1 = new QHBoxLayout();
        qlayout1->setObjectName("qlayout1");
        kquadratic = new QDoubleSpinBox(WidgetProjectiles);
        kquadratic->setObjectName("kquadratic");
        kquadratic->setSingleStep(0.100000000000000);

        qlayout1->addWidget(kquadratic);


        formLayout->setLayout(9, QFormLayout::ItemRole::FieldRole, qlayout1);


        retranslateUi(WidgetProjectiles);

        QMetaObject::connectSlotsByName(WidgetProjectiles);
    } // setupUi

    void retranslateUi(QWidget *WidgetProjectiles)
    {
        WidgetProjectiles->setWindowTitle(QCoreApplication::translate("WidgetProjectiles", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetProjectiles", "Gravity accel", nullptr));
        label->setText(QCoreApplication::translate("WidgetProjectiles", "Initial height", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetProjectiles", "Initial speed", nullptr));
        label_3->setText(QCoreApplication::translate("WidgetProjectiles", "Angle", nullptr));
        label_5->setText(QCoreApplication::translate("WidgetProjectiles", "Solver 1", nullptr));
        solver1->setItemText(0, QCoreApplication::translate("WidgetProjectiles", "Euler", nullptr));
        solver1->setItemText(1, QCoreApplication::translate("WidgetProjectiles", "Symplectic Euler", nullptr));
        solver1->setItemText(2, QCoreApplication::translate("WidgetProjectiles", "Midpoint", nullptr));
        solver1->setItemText(3, QCoreApplication::translate("WidgetProjectiles", "RK2", nullptr));
        solver1->setItemText(4, QCoreApplication::translate("WidgetProjectiles", "RK4", nullptr));
        solver1->setItemText(5, QCoreApplication::translate("WidgetProjectiles", "Verlet", nullptr));

        label_6->setText(QCoreApplication::translate("WidgetProjectiles", "Solver 2", nullptr));
        solver2->setItemText(0, QCoreApplication::translate("WidgetProjectiles", "Euler", nullptr));
        solver2->setItemText(1, QCoreApplication::translate("WidgetProjectiles", "Symplectic Euler", nullptr));
        solver2->setItemText(2, QCoreApplication::translate("WidgetProjectiles", "Midpoint", nullptr));
        solver2->setItemText(3, QCoreApplication::translate("WidgetProjectiles", "RK2", nullptr));
        solver2->setItemText(4, QCoreApplication::translate("WidgetProjectiles", "RK4", nullptr));
        solver2->setItemText(5, QCoreApplication::translate("WidgetProjectiles", "Verlet", nullptr));

        trajectory->setText(QCoreApplication::translate("WidgetProjectiles", "Show trajectory", nullptr));
        sameZ->setText(QCoreApplication::translate("WidgetProjectiles", "Same Z coordinate", nullptr));
        label_7->setText(QCoreApplication::translate("WidgetProjectiles", "KLinear", nullptr));
        label_8->setText(QCoreApplication::translate("WidgetProjectiles", "KQuadratic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetProjectiles: public Ui_WidgetProjectiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETPROJECTILES_H
