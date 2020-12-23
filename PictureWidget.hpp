#pragma once

#include <QWidget>
#include <QLabel>
#include <QImage>

class PictureWidget: public QWidget
{
	Q_OBJECT
public:
	PictureWidget(QString &filename, QWidget *parent = nullptr);
	
	QString getFilename() const;
	void setFilename(QString &filename);
	
	bool hasChanges() const;
	void save();
	
signals:
	void colorSelected(QColor color);
	
public slots:
	void changeColorKey(QColor color);
	
private:
	QLabel *background_label, *picture_label;
	QPixmap background_sprite, picture_sprite;
	QImage picture_image;
	
	QString filename;
	bool has_changes;
	
	void resetUI();
	
	void mousePressEvent(QMouseEvent *event) override;
};
