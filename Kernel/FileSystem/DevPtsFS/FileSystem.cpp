/*
 * Copyright (c) 2019-2020, Sergey Bugaev <bugaevc@serenityos.org>
 * Copyright (c) 2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Kernel/Devices/DeviceManagement.h>
#include <Kernel/FileSystem/DevPtsFS/FileSystem.h>
#include <Kernel/FileSystem/DevPtsFS/Inode.h>
#include <Kernel/TTY/SlavePTY.h>
#include <Kernel/Time/TimeManagement.h>

namespace Kernel {

ErrorOr<NonnullLockRefPtr<FileSystem>> DevPtsFS::try_create()
{
    return TRY(adopt_nonnull_lock_ref_or_enomem(new (nothrow) DevPtsFS));
}

DevPtsFS::DevPtsFS() = default;
DevPtsFS::~DevPtsFS() = default;

ErrorOr<void> DevPtsFS::initialize()
{
    m_root_inode = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) DevPtsFSInode(*this, 1, nullptr)));
    m_root_inode->m_metadata.inode = { fsid(), 1 };
    m_root_inode->m_metadata.mode = 0040555;
    m_root_inode->m_metadata.uid = 0;
    m_root_inode->m_metadata.gid = 0;
    m_root_inode->m_metadata.size = 0;
    m_root_inode->m_metadata.mtime = TimeManagement::boot_time();
    return {};
}

static unsigned inode_index_to_pty_index(InodeIndex inode_index)
{
    VERIFY(inode_index > 1);
    return inode_index.value() - 2;
}

Inode& DevPtsFS::root_inode()
{
    return *m_root_inode;
}

ErrorOr<NonnullRefPtr<Inode>> DevPtsFS::get_inode(InodeIdentifier inode_id) const
{
    if (inode_id.index() == 1)
        return *m_root_inode;

    unsigned pty_index = inode_index_to_pty_index(inode_id.index());
    auto* device = DeviceManagement::the().get_device(201, pty_index);
    VERIFY(device);

    auto inode = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) DevPtsFSInode(const_cast<DevPtsFS&>(*this), inode_id.index(), static_cast<SlavePTY*>(device))));
    inode->m_metadata.inode = inode_id;
    inode->m_metadata.size = 0;
    inode->m_metadata.uid = device->uid();
    inode->m_metadata.gid = device->gid();
    inode->m_metadata.mode = 0020600;
    inode->m_metadata.major_device = device->major();
    inode->m_metadata.minor_device = device->minor();
    inode->m_metadata.mtime = TimeManagement::boot_time();
    return inode;
}

}
