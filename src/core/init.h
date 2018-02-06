//
// Created by Ajat Prabha on 16-11-2017.
//

#ifndef SMS_INIT_H
#define SMS_INIT_H

#include <iostream>
#include "auth/user.h"
#include "../courses/courses.h"
#include "menu.h"
#include "view.h"

extern bool EXIT_CODE;          //Makes an environment variable to check for exit code

enum VIEW_CHOICES {
    SPLASH,
    LOGIN,
    REGISTER,
    DETAIL
};          //enum used to determine which derived class of View to call

extern VIEW_CHOICES view_choice;            //Makes an environment variable to store the above enum option

class Init {
public:
    static void init();             //Used to initialize startup values in memory
};

#endif //SMS_INIT_H
