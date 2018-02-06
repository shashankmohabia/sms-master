//
// Created by Ajat Prabha on 03-10-2017.
//
#include "user.h"

User* current_user = new AnonymousUser;

map<string, User> User::object_list = {};

User::User(const string& username, const string& first_name, const string& last_name)
{
    _username = username;
    _first_name = first_name;
    _last_name = last_name;
    _superuser_status = false;
}
string User::get_username() const
{
    return _username;
}
bool User::is_anonymous()
{
    return false;
}
bool User::is_authenticated()
{
    return true;
}
string User::get_fullname() const
{
    return _first_name+" "+_last_name;
}
void User::set_password(const string& password)
{
    _password = password;
}
bool User::check_password(const string& raw_password)
{
    return _password==raw_password;
}
User::User()
{
    _username = "guest";
    _first_name = "FGuest";
    _last_name = "LGuest";
    _superuser_status = false;
}
string User::get_shortname() const
{
    return _first_name;
}
User& User::save()
{
    if (User::all().find(this->get_username())!=User::all().end()) throw UserError("User already exists!");
    object_list.insert(pair<string, User>(this->get_username(), *this));
    return *this;
}
map<string, User>& User::all()
{
    return object_list;
}
void User::set_username(const string& username)
{
    _username = username;
}
User::User(const char* username, const char* first_name, const char* last_name)
{
    _username = username;
    _first_name = first_name;
    _last_name = last_name;
    _superuser_status = false;
}
void User::make_superuser()
{
    _superuser_status = true;
}
bool User::is_superuser()
{
    return _superuser_status;
}
AnonymousUser::AnonymousUser()
{
    _username = "anonymous";
    _first_name = "Anonymous";
    _last_name = "User";
}
bool AnonymousUser::is_anonymous()
{
    return true;
}
bool AnonymousUser::is_authenticated()
{
    return false;
}
void AnonymousUser::set_password(const string& /* unused */)
{
    throw UserError("No set_password method is implemented for Anonymous User");
}
bool AnonymousUser::check_password(const string& /* unused */)
{
    throw UserError("No check_password method is implemented for Anonymous User");
}
bool AnonymousUser::is_superuser()
{
    return false;
}
string UserError::print_error()
{
    return _err;
}
UserError::UserError(const string& err)
{
    _err = err;
}
int User::get_year()
{
    if (!this->is_superuser()) return _year;
    else return 0;
}
bool User::remove()
{
    auto it = User::all().find(this->get_username());
    object_list.erase(it);
    return true;
}
void User::set_year(int year)
{
    _year = year;
}
