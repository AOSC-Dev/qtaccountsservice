/****************************************************************************
 * This file is part of Qt AccountsService Addon.
 *
 * Copyright (c) 2012 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include "useraccount.h"
#include "useraccount_p.h"
#include "userinterface.h"

/*
 * UserAccountPrivate
 */

UserAccountPrivate::UserAccountPrivate()
    : user(0)
{
}

/*!
    \class VUserAcccount
    \brief The UserAccount class describes user accounts.

    This class describes user accounts retrieved with AccountsManager.

    \author Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>

    \sa AccountsManager
*/

/*!
    Constructs a UserAccount object for the specified \a uid.

    \param uid User identifier.
*/
UserAccount::UserAccount(uid_t uid)
    : d_ptr(new UserAccountPrivate)
{
    d_ptr->user =
        new OrgFreedesktopAccountsUserInterface("org.freedesktop.Accounts",
                                                QString("/org/freedesktop/Accounts/User%1").arg(uid),
                                                QDBusConnection::systemBus(),
                                                this);
}

/*!
    Constructs a UserAccount object from a specific objectPath in the form of
    /org/freedesktop/Accounts/UserUID where UID is user's uid.

    \param objectPath Accounts Service object path for the user account.
*/
UserAccount::UserAccount(const QString &objectPath)
    : d_ptr(new UserAccountPrivate)
{
    d_ptr->user =
        new OrgFreedesktopAccountsUserInterface("org.freedesktop.Accounts",
                                                objectPath,
                                                QDBusConnection::systemBus(),
                                                this);
}

/*!
    Destructor.
*/
UserAccount::~UserAccount()
{
    delete d_ptr;
}

/*!
    Returns the user identifier.
*/
uid_t UserAccount::userId() const
{
    Q_D(const UserAccount);
    return d->user->uid();
}

/*!
    Returns the account type.
*/
UserAccount::AccountType UserAccount::accountType() const
{
    Q_D(const UserAccount);
    return (UserAccount::AccountType)d->user->accountType();
}

/*!
    Sets the account type to \a type.

    \param type Account type.
*/
void UserAccount::setAccountType(AccountType type)
{
    Q_D(UserAccount);
    d->user->SetAccountType((int)type);
    emit accountTypeChanged();
}

/*!
    Returns whether this account is locked or not.
*/
bool UserAccount::isLocked() const
{
    Q_D(const UserAccount);
    return d->user->locked();
}

/*!
    Locks or unlocks the user account.
    Locking an account prevents the user from logging in.

    \param locked Whether to lock or unlock the user account.
*/
void UserAccount::setLocked(bool locked)
{
    Q_D(UserAccount);
    d->user->SetLocked(locked);
    emit lockedChanged();
}

/*!
    Returns whether the user account will automatically log in when the
    system starts up.
*/
bool UserAccount::automaticLogin() const
{
    Q_D(const UserAccount);
    return d->user->automaticLogin();
}

/*!
    Sets whether the user account will automatically log in when
    the system starts up.

    \param automaticLogin Whether automatic login is enabled for the user.
*/
void UserAccount::setAutomaticLogin(bool automaticLogin)
{
    Q_D(UserAccount);
    d->user->SetAutomaticLogin(automaticLogin);
    emit automaticLoginChanged();
}

/*!
    Returns how often the user has logged in.
*/
qlonglong UserAccount::loginFrequency() const
{
    Q_D(const UserAccount);
    return d->user->loginFrequency();
}

/*!
    Returns the last login time.
*/
qlonglong UserAccount::loginTime() const
{
    Q_D(const UserAccount);
    return d->user->loginTime();
}

/*!
    Returns the password mode for the user account.
*/
UserAccount::PasswordMode UserAccount::passwordMode() const
{
    Q_D(const UserAccount);
    return (UserAccount::PasswordMode)d->user->passwordMode();
}

/*!
    Sets the password mode for the user account.

    \param mode Password mode.
*/
void UserAccount::setPasswordMode(UserAccount::PasswordMode mode)
{
    Q_D(UserAccount);
    d->user->SetPasswordMode((int)mode);
    emit passwordModeChanged();
}

/*!
    Returns the password hint for the user.
*/
QString UserAccount::passwordHint() const
{
    Q_D(const UserAccount);
    return d->user->passwordHint();
}

/*!
    Returns whether the user is a local account or not.
*/
bool UserAccount::isLocalAccount() const
{
    Q_D(const UserAccount);
    return d->user->localAccount();
}

/*!
    Returns whether the user is a system account or not.
*/
bool UserAccount::isSystemAccount() const
{
    Q_D(const UserAccount);
    return d->user->systemAccount();
}

/*!
    Returns the user name.
*/
QString UserAccount::userName() const
{
    Q_D(const UserAccount);
    return d->user->userName();
}

/*!
    Sets the user name to \a userName.

    \param userName The new user name.
*/
void UserAccount::setUserName(const QString &userName)
{
    Q_D(UserAccount);
    d->user->SetUserName(userName);
    emit userNameChanged();
    emit displayNameChanged();
}

/*!
    Returns user's real name.
*/
QString UserAccount::realName() const
{
    Q_D(const UserAccount);
    return d->user->realName();
}

/*!
    Sets the user's real name to \a realName.

    \param realName Real name.
*/
void UserAccount::setRealName(const QString &realName)
{
    Q_D(UserAccount);
    d->user->SetRealName(realName);
    emit realNameChanged();
    emit displayNameChanged();
}

/*!
    Returns user's real name if not empty, otherwise the user name.
*/
QString UserAccount::displayName() const
{
    if (realName().isEmpty())
        return userName();
    return realName();
}

/*!
    Returns the home directory absolute path.
*/
QString UserAccount::homeDirectory() const
{
    Q_D(const UserAccount);
    return d->user->homeDirectory();
}

/*!
    Sets the home directory to \a homeDirectory.

    \param homeDirectory Home directory.
*/
void UserAccount::setHomeDirectory(const QString &homeDirectory)
{
    Q_D(UserAccount);
    d->user->SetHomeDirectory(homeDirectory);
    emit homeDirectoryChanged();
}

/*!
    Returns the login shell absolute path.
*/
QString UserAccount::shell() const
{
    Q_D(const UserAccount);
    return d->user->shell();
}

/*!
    Sets the login shell to \a shell.

    \param shell Login shell absolute path.
*/
void UserAccount::setShell(const QString &shell)
{
    Q_D(UserAccount);
    d->user->SetShell(shell);
    emit shellChanged();
}

/*!
    Returns user's picture absoulte path.
*/
QString UserAccount::iconFileName() const
{
    Q_D(const UserAccount);
    return d->user->iconFile();
}

/*!
    Sets users' picture absolute path to \a fileName.

    \param fileName Picture absolute path.
*/
void UserAccount::setIconFileName(const QString &fileName)
{
    Q_D(UserAccount);
    d->user->SetIconFile(fileName);
    emit iconFileNameChanged();
}

/*!
    Returns user's email address.
*/
QString UserAccount::email() const
{
    Q_D(const UserAccount);
    return d->user->email();
}

/*!
    Sets user's email address to \a email.

    \param email Email address.
*/
void UserAccount::setEmail(const QString &email)
{
    Q_D(UserAccount);
    d->user->SetEmail(email);
    emit emailChanged();
}

/*!
    Returns user language.
*/
QString UserAccount::language() const
{
    Q_D(const UserAccount);
    return d->user->language();
}

/*!
    Sets user language to \a language.

    \param language Language.
*/
void UserAccount::setLanguage(const QString &language)
{
    Q_D(UserAccount);
    d->user->SetLanguage(language);
    emit languageChanged();
}

/*!
    Returns user location.
*/
QString UserAccount::location() const
{
    Q_D(const UserAccount);
    return d->user->location();
}

/*!
    Sets user \a location.

    \param location Location.
*/
void UserAccount::setLocation(const QString &location)
{
    Q_D(UserAccount);
    d->user->SetLocation(location);
    emit locationChanged();
}

/*!
    Returns the X11 session for the user account.
*/
QString UserAccount::xsession() const
{
    Q_D(const UserAccount);
    return d->user->xSession();
}

/*!
    Sets the X11 session for the user account.

    \param session X11 session name.
*/
void UserAccount::setXSession(const QString &session)
{
    Q_D(UserAccount);
    d->user->SetXSession(session);
    emit xsessionChanged();
}

#include "moc_useraccount.cpp"