/*
 * Copyright (C) 2014 Moonlight Desktop Environment Team
 * Authors:
 *  Alexis López Zubieta
 * 
 * This file is part of Moonlight Desktop Environment Core.
 *
 * Moonlight Desktop Environment is free software: you can redistribute it 
 * and/or modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * Moonlight Desktop Environment is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Moonlight Desktop Environment. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MODULEMANAGER_H
#define	MODULEMANAGER_H

#include <usSharedLibrary.h>
#include <usModuleContext.h>

#include <QString>
#include <QHash>
#include <QStringList>

#include <string>
#include <algorithm>

#include "core/ICore.h"

#include <qt5xdg/XdgDesktopFile>

#include <usSharedLibrary.h>

#include <QHash>

US_USE_NAMESPACE


class ModuleManager : public Core::IModuleManager {
public:
    ModuleManager(const QHash<QString, QString> config);

    bool load(const QString &name);
    bool unload(const QString &name);
    void loadFromProfile(QSettings * profile);
    QList<QString> listAviableModules();
    QList<QString> listActiveModules();

    XdgDesktopFile * getModuleDescriptor(const QString moduleName);

    virtual ~ModuleManager();

private:
    QStringList m_descriptorsPaths;
    QHash<QString, SharedLibrary*> libs;
};

#endif	/* MODULEMANAGER_H */

