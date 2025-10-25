#include "widgetfountain.h"
#include "ui_widgetfountain.h"

WidgetFountain::WidgetFountain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFountain)
{
    ui->setupUi(this);

    connect(ui->btnUpdate, &QPushButton::clicked, this,
            [=] (void) { emit updatedParameters(); });
}

WidgetFountain::~WidgetFountain()
{
    delete ui;
}

double WidgetFountain::getGravity() const {
    return ui->gravity->value();
}

double WidgetFountain::getKElastic() const {
	return ui->kelastic->value();
}

double WidgetFountain::getKFriction() const {
    return ui->kfriction->value();
}
