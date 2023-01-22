#pragma once

#include <variant>
#include "definitions.h"

//gtkmm includes
#include <gtkmm/box.h>
#include <gtkmm/grid.h>

//fsd includes
#include "LLH.h"
#include "UTM.h"
#include "UTMREF.h"
#include "LocalRef.h"
#include "LocalCoordinates.h"

template<typename T>
class CoordVec;

using CoordVariant = std::variant<
                                CoordVec<fsd::Coord::UTMREF>*,
                                CoordVec<fsd::Coord::UTM>*,
                                CoordVec<fsd::Coord::LLHInt>*,
                                CoordVec<fsd::Coord::LocalCoordinates>*
                                >;

class CoordTrafoIO : public Gtk::Box {

    protected:
        Gtk::Box *main_layout {nullptr};

    public:
        CoordTrafoIO();

        CoordTrafoIO(const CoordTrafoIO&) = delete;
        CoordTrafoIO& operator=(const CoordTrafoIO&) = delete;

        CoordTrafoIO(CoordTrafoIO&&) = delete;
        CoordTrafoIO& operator=(CoordTrafoIO&&) = delete;

    private:
        Gtk::Grid *mainLayout;
        std::vector<CoordVariant> mInputs;

        void initMainLayout();
    
    public://slots
        template<typename Y>
        void inputChanged(CoordType eType, Y coords);

};