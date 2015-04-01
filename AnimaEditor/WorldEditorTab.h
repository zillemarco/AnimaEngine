//
//  WorldEditorTab.h
//  Anima
//
//  Created by Marco Zille on 04/12/14.
//
//

#ifndef __Anima__WorldEditorTab__
#define __Anima__WorldEditorTab__

#include <stdio.h>
#include <QFrame>
#include <QCloseEvent>
#include <QSettings>

class AnimaEditorDocument;

class WorldEditorTab : public QFrame
{
	Q_OBJECT
public:
	WorldEditorTab(AnimaEditorDocument* doc);
	
	void saveSettings(QSettings* settings);
	void readSettings(QSettings* settings);
	
private:
	AnimaEditorDocument* _document;
};

#endif /* defined(__Anima__WorldEditorTab__) */
