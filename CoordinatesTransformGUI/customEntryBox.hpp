#pragma once
#include <gtkmm/entry.h>

template<typename T>
class CoordVec;


template<typename T>
class customEntryBox : public Gtk::Entry{

    public:
        customEntryBox(CoordVec<T>& parent) : Gtk::Entry(), mParentVec{parent}
        {
            initEntryBox();
        }
    private:
        CoordVec<T>& mParentVec;
        void initEntryBox()
        {
            set_visible();
        }
};