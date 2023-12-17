#pragma once
#include <vector>

class Contact;

struct CollisionData
{
    // Hold contact array
    typedef std::vector<Contact*> Contacts;
    Contacts contacts;

    // Max contact for array
    int contactLeft;
};
