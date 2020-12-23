#pragma once

#include "PictureWidget.hpp"
#include "ColorDock.hpp"

#include <QMainWindow>
#include <QScrollArea>

class MainWindow: public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
	
private slots:
	void onOpen();
	void onClose();
	void onSave();
	void onSaveAs();
	void onQuit();
	
signals:
	void enableMenuItems(bool yes_no);
	
private:
	QScrollArea *scroll_area;
	PictureWidget *picture_widget;
	ColorDock *color_dock;
	
	bool askForSave();
};
