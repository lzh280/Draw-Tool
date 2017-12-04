﻿#include "xypensettingwidget.h"

XYPenSettingWidget *XYPenSettingWidget::getInstance()
{
    static XYPenSettingWidget *instance = NULL;
    if (instance == NULL)
    {
        instance = new XYPenSettingWidget;
    }
    return instance;
}

XYPenSettingWidget::XYPenSettingWidget(QWidget *parent)
    : XYMovableWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint
                         | Qt::WindowType_Mask);

#define ADDITEM(instance, value) instance->addItem(#value, (int)value)
    int row = 0;
    QLabel *penColor = new QLabel(QStringLiteral("画笔颜色"));
    selectPenColor = new XYLabel(QColor("green"));
    QLabel *penStyle = new QLabel(QStringLiteral("画笔风格"));
    selectPenStyle = new QComboBox;
    ADDITEM(selectPenStyle, Qt::SolidLine);
    ADDITEM(selectPenStyle, Qt::DashLine);
    ADDITEM(selectPenStyle, Qt::DotLine);
    ADDITEM(selectPenStyle, Qt::DashDotLine);
    ADDITEM(selectPenStyle, Qt::DashDotDotLine);
    ADDITEM(selectPenStyle, Qt::NoPen);
    QLabel *penOpacity = new QLabel(QStringLiteral("画笔透明度"));
    penOpacityBox = new QSlider;
    penOpacityBox->setOrientation(Qt::Horizontal);
    penOpacityBox->setMinimum(0);
    penOpacityBox->setMaximum(255);
    penOpacityBox->setValue(0);
    QLabel *penWidth = new QLabel(QStringLiteral("画笔宽度"));
    widthBox = new QSlider;
    widthBox->setOrientation(Qt::Horizontal);
    widthBox->setMinimum(1);
    widthBox->setMaximum(50);
    widthBox->setValue(1);
    QGroupBox *penBox = new QGroupBox(QStringLiteral("画笔设置"));
    QGridLayout *penLayout = new QGridLayout(penBox);
    row = 0;
    penLayout->addWidget(penColor, row, 0);
    penLayout->addWidget(selectPenColor, row++, 1);
    penLayout->addWidget(penStyle, row, 0);
    penLayout->addWidget(selectPenStyle, row++, 1);
    penLayout->addWidget(penOpacity, row, 0);
    penLayout->addWidget(penOpacityBox, row++, 1);
    penLayout->addWidget(penWidth, row, 0);
    penLayout->addWidget(widthBox, row++, 1);

    QLabel *brushColor = new QLabel(QStringLiteral("画刷颜色"));
    selectBrushColor = new XYLabel(QColor("green"));
    QLabel *brushStyle = new QLabel(QStringLiteral("画刷风格"));
    selectBrushStyle = new QComboBox;
    ADDITEM(selectBrushStyle, Qt::SolidPattern);
    ADDITEM(selectBrushStyle, Qt::Dense1Pattern);
    ADDITEM(selectBrushStyle, Qt::HorPattern);
    ADDITEM(selectBrushStyle, Qt::VerPattern);
    ADDITEM(selectBrushStyle, Qt::CrossPattern);
    ADDITEM(selectBrushStyle, Qt::BDiagPattern);
    ADDITEM(selectBrushStyle, Qt::FDiagPattern);
    ADDITEM(selectBrushStyle, Qt::DiagCrossPattern);
    ADDITEM(selectBrushStyle, Qt::LinearGradientPattern);
    ADDITEM(selectBrushStyle, Qt::ConicalGradientPattern);
    ADDITEM(selectBrushStyle, Qt::RadialGradientPattern);
    ADDITEM(selectBrushStyle, Qt::NoBrush);
    QLabel *brushOpacity = new QLabel(QStringLiteral("画刷透明度"));
    brushOpacityBox = new QSlider;
    brushOpacityBox->setOrientation(Qt::Horizontal);
    brushOpacityBox->setMinimum(0);
    brushOpacityBox->setMaximum(255);
    brushOpacityBox->setValue(0);
    QGroupBox *brushBox = new QGroupBox(QStringLiteral("画刷设置"));
    QGridLayout *brushLayout = new QGridLayout(brushBox);
    row = 0;
    brushLayout->addWidget(brushColor, row, 0);
    brushLayout->addWidget(selectBrushColor, row++, 1);
    brushLayout->addWidget(brushStyle, row, 0);
    brushLayout->addWidget(selectBrushStyle, row++, 1);
    brushLayout->addWidget(brushOpacity, row, 0);
    brushLayout->addWidget(brushOpacityBox, row++, 1);

    QLabel *fontFamily = new QLabel(QStringLiteral("字体"));
    selectFonts = new QFontComboBox;
    QLabel *fontSize = new QLabel(QStringLiteral("字体大小"));
    sizeBox = new QSlider;
    sizeBox->setOrientation(Qt::Horizontal);
    sizeBox->setMinimum(1);
    sizeBox->setMaximum(100);
    sizeBox->setValue(10);
    QGroupBox *fontBox = new QGroupBox(QStringLiteral("字体设置"));
    QGridLayout *fontLayout = new QGridLayout(fontBox);
    row = 0;
    fontLayout->addWidget(fontFamily, row, 0);
    fontLayout->addWidget(selectFonts, row++, 1);
    fontLayout->addWidget(fontSize, row, 0);
    fontLayout->addWidget(sizeBox, row++, 1);

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(penBox);
    mainlayout->addWidget(brushBox);
    mainlayout->addWidget(fontBox);

}

XYPenSettingWidget::~XYPenSettingWidget()
{

}
QPen XYPenSettingWidget::getMoPen()
{
    QColor color = selectPenColor->getColor();
    color.setAlpha(255 - penOpacityBox->value());
    moPen.setColor(color);
    moPen.setStyle((Qt::PenStyle)selectPenStyle->currentData().toInt());
    moPen.setWidth(widthBox->value());
    return moPen;
}

void XYPenSettingWidget::setMoPen(const QPen &value)
{
    moPen = value;
}
QFont XYPenSettingWidget::getMoFont()
{
    moFont = selectFonts->currentFont();
    moFont.setPixelSize(sizeBox->value());
    return moFont;
}

void XYPenSettingWidget::setMoFont(const QFont &value)
{
    moFont = value;
}
QBrush XYPenSettingWidget::getMoBrush()
{
    QColor color = selectBrushColor->getColor();
    color.setAlpha(255 - brushOpacityBox->value());
    moBrush.setStyle((Qt::BrushStyle)selectBrushStyle->currentData().toInt());
    moBrush.setColor(color);
    return moBrush;
}

void XYPenSettingWidget::setMoBrush(const QBrush &value)
{
    moBrush = value;
}

void XYLabel::mslotSelectColor()
{
    color = QColorDialog::getColor();
    emit colorChanged(color);
    update();
}

void XYLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(0, 0, 0, 0));
    painter.setBrush(color);
    painter.drawRect(rect());
}

void XYLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (rect().contains(event->pos()))
    {
        emit selectColor();
    }
}
XYLabel::XYLabel(const QColor &color, QWidget *parent)
    :QLabel(parent), color(color)
{
    setMaximumHeight(25);
    connect(this, SIGNAL(selectColor()), this, SLOT(mslotSelectColor()));
}

QColor XYLabel::getColor() const
{
    return color;
}

void XYLabel::setColor(const QColor &value)
{
    color = value;
}

QSize XYLabel::sizeHint() const
{
    return QSize(50, 25);
}
