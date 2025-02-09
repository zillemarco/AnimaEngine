//
//  AEResourcesManagerTab.h
//  Anima
//
//  Created by Marco Zille on 04/12/14.
//
//

#ifndef __Anima__ResourceManagerTab__
#define __Anima__ResourceManagerTab__

#include <stdio.h>
#include <QFrame>
#include <QCloseEvent>
#include <QSplitter>
#include <QSettings>

class AEDocument;
class AEResourcesManagerModelViewer;
class AELoadedResourcesTreeView;

class AEResourcesManagerTab : public QFrame
{
	Q_OBJECT
public:
	AEResourcesManagerTab(AEDocument* doc);
	
	void saveSettings(QSettings* settings);
	void readSettings(QSettings* settings);
	
public:
	void LoadResourcesTree();
	
	AEResourcesManagerModelViewer* GetModelViewer() const { return _modelViewer; }

private:
	AEDocument* _document;
	
	QSplitter* _mainSplitter;
	AELoadedResourcesTreeView* _resourcesTreeView;
	AEResourcesManagerModelViewer* _modelViewer;
};

#endif /* defined(__Anima__ResourceManagerTab__) */
