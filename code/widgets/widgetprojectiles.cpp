#include "widgetprojectiles.h"
#include "ui_widgetprojectiles.h"

WidgetProjectiles::WidgetProjectiles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetProjectiles)
{
    ui->setupUi(this);
}

WidgetProjectiles::~WidgetProjectiles()
{
    delete ui;
}

double WidgetProjectiles::getHeight() const {
    return ui->height->value();
}

double WidgetProjectiles::getGravity() const {
    return ui->gravity->value();
}

double WidgetProjectiles::getAngle() const {
    return ui->angle->value();
}

double WidgetProjectiles::getSpeed() const {
    return ui->speed->value();
}

int WidgetProjectiles::getSolver1() const {
    return ui->solver1->currentIndex();
}

int WidgetProjectiles::getSolver2() const {
    return ui->solver2->currentIndex();
}

bool WidgetProjectiles::renderSameZ() const {
    return ui->sameZ->isChecked();
}

bool WidgetProjectiles::renderTrajectory() const {
    return ui->trajectory->isChecked();
}

void WidgetProjectiles::setSolver1(int idx) {
    ui->solver1->setCurrentIndex(idx);
}

void WidgetProjectiles::setSolver2(int idx) {
    ui->solver2->setCurrentIndex(idx);
}

double WidgetProjectiles::getKLinear() const{
    return ui->klinear->value();
}
double WidgetProjectiles::getKQuadratic() const{
    return ui->kquadratic->value();
}

double WidgetProjectiles::getReynoldsNumber() const{
    return ui->reynolds->value();
}
