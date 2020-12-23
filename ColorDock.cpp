#include "ColorDock.hpp"

#include <QColorDialog>

ColorDock::ColorDock(QWidget *parent):
	QWidget(parent),
	color_label(new QLabel(this)),
	color_button(new QPushButton(tr("Change color"), this)),
	selected_color(Qt::black)
{
	setFixedHeight(48);
	
	color_label->setGeometry(4, 4, 64, 32);
	color_button->move(68, 4);
	color_button->setFixedHeight(32);
	
//	updateUI();
	
	connect(color_button, &QPushButton::clicked, this, &ColorDock::setColor);
}

void ColorDock::updateUI()
{
	QPixmap pixmap(64, 32);
	pixmap.fill(selected_color);
	
	color_label->setPixmap(pixmap);
}

QColor ColorDock::getColor() const
{
	return selected_color;
}

void ColorDock::setColor()
{
	QColor color = QColorDialog::getColor(selected_color, this, tr("Pick a color"));
	
	if (color.isValid())
		changeColorKey(color);
}

void ColorDock::changeColorKey(QColor color)
{
	selected_color = color;
	updateUI();
	
	emit colorSelected(color);
}
