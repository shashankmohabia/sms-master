//
// Created by Ajat Prabha on 22-11-2017.
//

#include "menu.h"
#include "init.h"

//Initialising global value
bool START = true;

Menu* Menu::getInstance()
{
    return new Menu;
}

//This method decides which view to call based upon value stored in view_choice
void Menu::display()
{
    //system("cls");
    delete global_view;
    if (START) {
        global_view = new SplashView;
        START = false;
        global_view->display();
        return;
    }
    switch (view_choice) {
    case LOGIN: {
        global_view = new LoginView;
        break;
    }
    case REGISTER: {
        global_view = new RegisterView;
        break;
    }
    case DETAIL: {
        if (current_user->is_superuser()) global_view = new AdminDetailView;
        else global_view = new StudentDetailView;
        break;
    }
    default: {
        cout << "Invalid Choice\n";
        EXIT_CODE = true;
        break;
    }
    }
    global_view->display();
    cout << endl;
    //if (view_choice==VIEW_CHOICES(DETAIL)) system("pause");
}
