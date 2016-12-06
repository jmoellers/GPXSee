#include <QtGlobal>
#include <QTranslator>
#include <QLocale>
#include <QFileOpenEvent>
#include <QNetworkProxyFactory>
#include <QPixmapCache>
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QGLFormat>
#else // QT 5
#include <QSurfaceFormat>
#endif // QT 5
#include "gui.h"
#include "app.h"


App::App(int &argc, char **argv) : QApplication(argc, argv),
  _argc(argc), _argv(argv)
{
	_translator = new QTranslator();

	QString locale = QLocale::system().name();
	_translator->load(QString(":/lang/gpxsee_") + locale);
	installTranslator(_translator);
#ifdef Q_OS_MAC
	setAttribute(Qt::AA_DontShowIconsInMenus);
#endif // Q_OS_MAC

	QNetworkProxyFactory::setUseSystemConfiguration(true);

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	QGLFormat fmt;
	fmt.setSamples(10);
	QGLFormat::setDefaultFormat(fmt);
#else
	QSurfaceFormat fmt;
	fmt.setSamples(4);
	QSurfaceFormat::setDefaultFormat(fmt);
#endif

	QPixmapCache::setCacheLimit(65536);

	_gui = new GUI();
}

App::~App()
{
	delete _gui;
	delete _translator;
}

void App::run()
{
	_gui->show();

	for (int i = 1; i < _argc; i++)
		_gui->openFile(QString::fromLocal8Bit(_argv[i]));

	exec();
}

bool App::event(QEvent *event)
{
	if (event->type() == QEvent::FileOpen) {
		QFileOpenEvent *e = static_cast<QFileOpenEvent *>(event);
		return _gui->openFile(e->file());
	}

	return QApplication::event(event);
}
