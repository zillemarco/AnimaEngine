//
//  AnimaEditorMainWindow.h
//  Anima
//
//  Created by Marco Zille on 03/12/14.
//
//

#ifndef __Anima__AnimaEditorMainWindow__
#define __Anima__AnimaEditorMainWindow__

#include <QMainWindow>

class AnimaEditorDocument;
class ResourceManagerTab;
class WorldEditorTab;
class EditWindow;
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;
class QGridLayout;
class QShortcut;
#include <QList>

struct RecentFileElement
{
	QString _filePath;
	QString _fileName;
};

class AnimaEditorMainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	AnimaEditorMainWindow();
	
protected:
	void closeEvent(QCloseEvent *event);
	
private slots:
	void newProject();
	void openProject();
	bool closeProject();
	void updateMenus();
	
	void importModel();
	void importTexture();
	void addNewMaterial();

	void setActiveSubWindow(QWidget *window);
	
	void readRecentFileList();
	void saveRecentFileList();
	
	void loadProjectFromRecentFiles(int index);

private:
	void createActions();
	void createMenus();
	void createStatusBar();
	void readSettings();
	void writeSettings();
		
	QMdiArea*		_mdiArea;
	QSignalMapper*	_windowMapper;
	QSignalMapper*	_recentFilesMapper;
		
	QMenu*		_fileMenu;
	QMenu*		_resourcesMenu;
	QMenu*		_recentFilesMenu;
	
	QAction*	_newAct;
	QAction*	_openAct;
	QAction*	_closeProjectAct;
	QAction*	_exitAct;
	
	QList<QAction*> _recentFilesAction;
	
	QAction*	_importModelAct;
	QAction*	_importTextureAct;
	QAction*	_addNewMaterialAct;
	
	AnimaEditorDocument* _activeDocument;
	
	ResourceManagerTab* _resourceManagerTab;
	WorldEditorTab*		_worldEditorTab;
	
	QList<RecentFileElement> _recentFiles;
};

#endif /* defined(__Anima__AnimaEditorMainWindow__) */
