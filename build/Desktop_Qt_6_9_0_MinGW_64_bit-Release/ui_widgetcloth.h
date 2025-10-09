/********************************************************************************
** Form generated from reading UI file 'widgetcloth.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETCLOTH_H
#define UI_WIDGETCLOTH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetCloth
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *gravity;
    QLabel *label_3;
    QDoubleSpinBox *springStiffness;
    QLabel *label_6;
    QDoubleSpinBox *springDamping;
    QCheckBox *showParticles;
    QPushButton *btnUpdate;
    QFrame *line;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *sizeX;
    QDoubleSpinBox *sizeY;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *numParticlesX;
    QSpinBox *numParticlesY;
    QLabel *label_7;
    QComboBox *integrators;
    QLabel *label_5;
    QDoubleSpinBox *particleRad;
    QLabel *label_8;
    QPushButton *btnFreeAnchors;

    void setupUi(QWidget *WidgetCloth)
    {
        if (WidgetCloth->objectName().isEmpty())
            WidgetCloth->setObjectName("WidgetCloth");
        WidgetCloth->resize(284, 457);
        formLayout = new QFormLayout(WidgetCloth);
        formLayout->setObjectName("formLayout");
        label = new QLabel(WidgetCloth);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        gravity = new QDoubleSpinBox(WidgetCloth);
        gravity->setObjectName("gravity");
        gravity->setMaximum(100.000000000000000);
        gravity->setSingleStep(1.000000000000000);
        gravity->setValue(9.810000000000000);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, gravity);

        label_3 = new QLabel(WidgetCloth);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_3);

        springStiffness = new QDoubleSpinBox(WidgetCloth);
        springStiffness->setObjectName("springStiffness");
        springStiffness->setMaximum(1000.000000000000000);
        springStiffness->setSingleStep(10.000000000000000);
        springStiffness->setValue(100.000000000000000);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, springStiffness);

        label_6 = new QLabel(WidgetCloth);
        label_6->setObjectName("label_6");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_6);

        springDamping = new QDoubleSpinBox(WidgetCloth);
        springDamping->setObjectName("springDamping");
        springDamping->setMaximum(1.000000000000000);
        springDamping->setSingleStep(0.100000000000000);
        springDamping->setValue(0.500000000000000);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, springDamping);

        showParticles = new QCheckBox(WidgetCloth);
        showParticles->setObjectName("showParticles");
        showParticles->setChecked(false);

        formLayout->setWidget(4, QFormLayout::ItemRole::SpanningRole, showParticles);

        btnUpdate = new QPushButton(WidgetCloth);
        btnUpdate->setObjectName("btnUpdate");

        formLayout->setWidget(5, QFormLayout::ItemRole::SpanningRole, btnUpdate);

        line = new QFrame(WidgetCloth);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        formLayout->setWidget(6, QFormLayout::ItemRole::SpanningRole, line);

        label_2 = new QLabel(WidgetCloth);
        label_2->setObjectName("label_2");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        sizeX = new QDoubleSpinBox(WidgetCloth);
        sizeX->setObjectName("sizeX");
        sizeX->setMaximum(200.000000000000000);
        sizeX->setSingleStep(10.000000000000000);
        sizeX->setValue(90.000000000000000);

        horizontalLayout->addWidget(sizeX);

        sizeY = new QDoubleSpinBox(WidgetCloth);
        sizeY->setObjectName("sizeY");
        sizeY->setMaximum(200.000000000000000);
        sizeY->setSingleStep(10.000000000000000);
        sizeY->setValue(150.000000000000000);

        horizontalLayout->addWidget(sizeY);


        formLayout->setLayout(7, QFormLayout::ItemRole::FieldRole, horizontalLayout);

        label_4 = new QLabel(WidgetCloth);
        label_4->setObjectName("label_4");

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, label_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        numParticlesX = new QSpinBox(WidgetCloth);
        numParticlesX->setObjectName("numParticlesX");
        numParticlesX->setMinimum(2);
        numParticlesX->setMaximum(1000);
        numParticlesX->setSingleStep(5);
        numParticlesX->setValue(60);

        horizontalLayout_2->addWidget(numParticlesX);

        numParticlesY = new QSpinBox(WidgetCloth);
        numParticlesY->setObjectName("numParticlesY");
        numParticlesY->setMinimum(2);
        numParticlesY->setMaximum(1000);
        numParticlesY->setSingleStep(5);
        numParticlesY->setValue(100);

        horizontalLayout_2->addWidget(numParticlesY);


        formLayout->setLayout(8, QFormLayout::ItemRole::FieldRole, horizontalLayout_2);

        label_7 = new QLabel(WidgetCloth);
        label_7->setObjectName("label_7");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_7);

        integrators = new QComboBox(WidgetCloth);
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->addItem(QString());
        integrators->setObjectName("integrators");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, integrators);

        label_5 = new QLabel(WidgetCloth);
        label_5->setObjectName("label_5");

        formLayout->setWidget(9, QFormLayout::ItemRole::LabelRole, label_5);

        particleRad = new QDoubleSpinBox(WidgetCloth);
        particleRad->setObjectName("particleRad");
        particleRad->setMinimum(0.010000000000000);
        particleRad->setMaximum(100.000000000000000);
        particleRad->setSingleStep(0.100000000000000);
        particleRad->setValue(0.500000000000000);

        formLayout->setWidget(9, QFormLayout::ItemRole::FieldRole, particleRad);

        label_8 = new QLabel(WidgetCloth);
        label_8->setObjectName("label_8");

        formLayout->setWidget(10, QFormLayout::ItemRole::LabelRole, label_8);

        btnFreeAnchors = new QPushButton(WidgetCloth);
        btnFreeAnchors->setObjectName("btnFreeAnchors");

        formLayout->setWidget(10, QFormLayout::ItemRole::FieldRole, btnFreeAnchors);


        retranslateUi(WidgetCloth);

        QMetaObject::connectSlotsByName(WidgetCloth);
    } // setupUi

    void retranslateUi(QWidget *WidgetCloth)
    {
        WidgetCloth->setWindowTitle(QCoreApplication::translate("WidgetCloth", "Form", nullptr));
        label->setText(QCoreApplication::translate("WidgetCloth", "Gravity", nullptr));
        label_3->setText(QCoreApplication::translate("WidgetCloth", "Spring stiffness", nullptr));
        label_6->setText(QCoreApplication::translate("WidgetCloth", "Spring damp", nullptr));
        showParticles->setText(QCoreApplication::translate("WidgetCloth", "Show particles", nullptr));
        btnUpdate->setText(QCoreApplication::translate("WidgetCloth", "Update", nullptr));
        label_2->setText(QCoreApplication::translate("WidgetCloth", "Dimensions", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetCloth", "Num particles", nullptr));
        label_7->setText(QCoreApplication::translate("WidgetCloth", "Integrator", nullptr));
        integrators->setItemText(0, QCoreApplication::translate("WidgetCloth", "Euler", nullptr));
        integrators->setItemText(1, QCoreApplication::translate("WidgetCloth", "Symplectic Euler", nullptr));
        integrators->setItemText(2, QCoreApplication::translate("WidgetCloth", "Midpoint", nullptr));
        integrators->setItemText(3, QCoreApplication::translate("WidgetCloth", "RK2", nullptr));
        integrators->setItemText(4, QCoreApplication::translate("WidgetCloth", "RK4", nullptr));
        integrators->setItemText(5, QCoreApplication::translate("WidgetCloth", "Verlet", nullptr));

        label_5->setText(QCoreApplication::translate("WidgetCloth", "Particle radius", nullptr));
        label_8->setText(QCoreApplication::translate("WidgetCloth", "F: fix particle", nullptr));
        btnFreeAnchors->setText(QCoreApplication::translate("WidgetCloth", "Free anchors", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetCloth: public Ui_WidgetCloth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETCLOTH_H
