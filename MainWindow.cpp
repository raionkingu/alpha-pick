#include "MainWindow.hpp"

#include <QApplication>
#include <QMenuBar>
#include <QDockWidget>

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	scroll_area(new QScrollArea(this))
{
	QMenu *file_menu = menuBar()->addMenu(tr("&File"));
	
	QAction *action_open = new QAction(tr("&Open..."), this);
	action_open->setIcon(QIcon::fromTheme("document-open"));
	action_open->setShortcut(QKeySequence::Open);
	connect(action_open, &QAction::triggered, this, &MainWindow::onOpen);
	file_menu->addAction(action_open);
	
	QAction *action_close = new QAction(tr("&Close..."), this);
	action_close->setIcon(QIcon::fromTheme("document-close"));
	action_close->setShortcut(QKeySequence::Close);
	connect(action_close, &QAction::triggered, this, &MainWindow::onClose);
	action_close->setEnabled(false);
	connect(this, &MainWindow::enableMenuItems, action_close, &QAction::setEnabled);
	file_menu->addAction(action_close);
	
	file_menu->addSeparator();
	
	QAction *action_save = new QAction(tr("&Save"), this);
	action_save->setIcon(QIcon::fromTheme("document-save"));
	action_save->setShortcut(QKeySequence::Save);
	connect(action_save, &QAction::triggered, this, &MainWindow::onSave);
	action_save->setEnabled(false);
	connect(this, &MainWindow::enableMenuItems, action_save, &QAction::setEnabled);
	file_menu->addAction(action_save);
	
	QAction *action_save_as = new QAction(tr("Save as..."), this);
	action_save_as->setIcon(QIcon::fromTheme("document-save-as"));
	action_save_as->setShortcut(QKeySequence::SaveAs);
	connect(action_save_as, &QAction::triggered, this, &MainWindow::onSaveAs);
	action_save_as->setEnabled(false);
	connect(this, &MainWindow::enableMenuItems, action_save_as, &QAction::setEnabled);
	file_menu->addAction(action_save_as);
	
	file_menu->addSeparator();
	
	QAction *action_quit = new QAction(tr("&Quit"), this);
	action_quit->setIcon(QIcon::fromTheme("document-exit"));
	action_quit->setShortcut(QKeySequence::Quit);
	connect(action_quit, &QAction::triggered, this, &MainWindow::onQuit);
	file_menu->addAction(action_quit);
	
	scroll_area->setBackgroundRole(QPalette::Dark);
	scroll_area->setFrameStyle(QFrame::NoFrame);
	setCentralWidget(scroll_area);

	color_dock = new ColorDock(this);
	QDockWidget *dock = new QDockWidget(this);
	dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dock->setTitleBarWidget(new QWidget(dock));
	addDockWidget(Qt::BottomDockWidgetArea, dock);
	dock->setWidget(color_dock);
}

void MainWindow::onOpen()
{
	if (picture_widget && picture_widget->hasChanges())
		if (!askForSave())
			return;
	
	QString filename = QFileDialog::getOpenFileName(
		this,
		tr("Choose an image"),
		QString(),
		tr("Images (*.png *.bmp *.jpg)")
	);
	
	if (!filename.isEmpty())
	{
		if (picture_widget)
			delete picture_widget;
		
		picture_widget = new PictureWidget(filename, scroll_area);
		scroll_area->setWidget(picture_widget);
		emit enableMenuItems(true);
	}
}

void MainWindow::onClose()
{
//	Closing should have been deactivated if no picture was open
	assert(picture_widget != nullptr);
	if (picture_widget->hasChanges())
		if (!askForSave())
			return;
	
	delete picture_widget;
	picture_widget = nullptr;
	emit enableMenuItems(false);
}

void MainWindow::onSave()
{
//	Saving should have been deactivated if no picture was open
	assert(picture_widget != nullptr);
	if (picture_widget->getFilename().isEmpty())
		onSaveAs();
	else
		picture_widget->save();
}

void MainWindow::onSaveAs()
{
//	Saving should have been deactivated if no picture was open
	assert(picture_widget != nullptr);
	
	QString filename = QFileDialog::getSaveFileName(
		this,
		tr("Choose an image"),
		QString(),
		tr("Images (*.png)")
	);
	
	if (!filename.isEmpty())
	{
		picture_widget->setFilename(filename);
		picture_widget->save();
	}
}

void MainWindow::onQuit()
{
	if (picture_widget && picture_widget->hasChanges())
		if (!askForSave())
			return;
	
	qApp->quit();
}

bool MainWindow::askForSave()
{
	QMessageBox box;
	
	box.setText(tr("The document has been modified."));
	box.setInformativeText(tr("Do you want to save your changes ?"));
	box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	box.setDefaultButton(QMessageBox::Save);
	
	switch (box.exec())
	{
	case QMessageBox::Save:
		onSave();
		return true;
	case QMessageBox::Discard:
		return true;
	case QMessageBox::Cancel:
		return false;
	default:
		return true;
	}
}
