#include "form.h"
#include "ui_form.h"
#include "gsmainscene.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

extern GsRootItem * m_pRootItem;
void Form::on_LineButton_clicked()
{
    m_pRootItem->setCurType(Shape_Line);
}

void Form::on_RectangeButton_clicked()
{
    m_pRootItem->setCurType(Shape_Rectange);
}

void Form::on_CircleButton_clicked()
{
    m_pRootItem->setCurType(Shape_Circle);
}

void Form::on_OvalButton_clicked()
{
    m_pRootItem->setCurType(Shape_Oval);
}
