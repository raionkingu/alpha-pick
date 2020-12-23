#include "PictureWidget.hpp"

#include <QMouseEvent>

PictureWidget::PictureWidget(QString &filename, QWidget *parent):
	QWidget(parent),
	background_label(new QLabel(this)),
	picture_label(new QLabel(this)),
	background_sprite(),
	picture_sprite(),
	picture_image(filename),
	filename(filename),
	has_changes(false)
{
	resetUI();
}

static QPixmap create_background(const size_t width, const size_t height)
{
	QImage bg(width, height, QImage::Format_RGB32);
	
	for (size_t i = 0; i < width; ++i)
		for (size_t j = 0; j < height; ++j)
			bg.setPixelColor(i, j, (((i/32)%2) ^ ((j/32)%2))? Qt::darkGray : Qt::gray);
	
	return QPixmap::fromImage(bg);
}

void PictureWidget::resetUI()
{
	assert(background_label != nullptr);
	assert(picture_label != nullptr);
	
	const auto w = picture_image.width();
	const auto h = picture_image.height();
	
	resize(w, h);
	
	background_sprite = create_background(w, h);
	background_label->setPixmap(background_sprite);
	
	picture_sprite = QPixmap::fromImage(picture_image);
	picture_label->setPixmap(picture_sprite);
}

QString PictureWidget::getFilename() const
{
	return filename;
}

void PictureWidget::setFilename(QString &filename)
{
	this->filename = filename;
}

bool PictureWidget::hasChanges() const
{
	return has_changes;
}

void PictureWidget::save()
{
	picture_sprite.save(filename);
	has_changes = false;
}

void PictureWidget::changeColorKey(QColor color)
{
	QImage image(picture_image.copy());

	const int w = image.width();
	const int h = image.height();

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			if (image.pixelColor(i, j) == color)
			{
				image.setPixelColor(i, j, QColor(0, 0, 0, 0));
				has_changes = true;
			}
		}
	}

	picture_sprite.convertFromImage(image);
	picture_label->setPixmap(picture_sprite);
}

void PictureWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit colorSelected(picture_image.pixelColor(event->x(), event->y()));
	}
}
