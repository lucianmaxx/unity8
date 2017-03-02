/*
 * Copyright (C) 2017 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MOCKWINDOMANAGEMENTPOLICY_H
#define MOCKWINDOMANAGEMENTPOLICY_H

#include <QObject>
#include <QMultiMap>
#include <QVector>

#include <miral/window.h>
#include <memory>
#include <unordered_set>

namespace miral {
class Workspace {};
}

// A Fake window management policy for the mock.
class Q_DECL_EXPORT WindowManagementPolicy : public QObject
{
    Q_OBJECT
public:
    WindowManagementPolicy();

    static WindowManagementPolicy *instance();

    std::shared_ptr<miral::Workspace> createWorkspace();
    void releaseWorkspace(const std::shared_ptr<miral::Workspace>& workspace);

    void forEachWindowInWorkspace(std::shared_ptr<miral::Workspace> const& workspace,
                                  std::function<void(miral::Window const&)> const& callback);

    void moveWorkspaceContentToWorkspace(const std::shared_ptr<miral::Workspace>& to,
                                         const std::shared_ptr<miral::Workspace>& from);

    void addWindow(const miral::Window& window);

    void setActiveWorkspace(const std::shared_ptr<miral::Workspace>& workspace);

Q_SIGNALS:
    void windowAdded(const miral::Window& window);
    void windowsAddedToWorkspace(const std::shared_ptr<miral::Workspace> &workspace, const std::vector<miral::Window> &windows);
    void windowsAboutToBeRemovedFromWorkspace(const std::shared_ptr<miral::Workspace> &workspace, const std::vector<miral::Window> &windows);

private:
    std::weak_ptr<miral::Workspace> m_activeWorkspace;
    std::shared_ptr<miral::Workspace> m_dummyWorkspace;
    std::unordered_set<std::shared_ptr<miral::Workspace>> m_workspaces;

    QMultiMap<miral::Workspace*, miral::Window> m_windows;
};
#endif // UNITY_WINDOWMANAGEMENTPOLICY_H
