#pragma once

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

class ColorDock: public QWidget
{
	Q_OBJECT
public:
	explicit ColorDock(QWidget *parent = nullptr);
	
	QColor getColor() const;
	
signals:
	void colorSelected(QColor);
	
public slots:
	void changeColorKey(QColor color);
	
private slots:
	void setColor();
	
private:
	QLabel *color_label;
	QPushButton *color_button;
	QColor selected_color;
	
	void updateUI();
};
