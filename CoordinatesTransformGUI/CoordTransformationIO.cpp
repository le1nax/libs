#include "CoordTransformationIO.h"
#include "CoordVec.hpp"
#include <gtkmm/label.h>


using namespace std;
using namespace Gtk;
using namespace fsd::Coord;
CoordTrafoIO::CoordTrafoIO() : Gtk::Box(ORIENTATION_HORIZONTAL){
    initMainLayout();
}

void CoordTrafoIO::initMainLayout(){
    mainLayout = make_managed<Grid>();
    mainLayout->set_hexpand(false);
    mainLayout->set_vexpand(false);
    mainLayout->set_row_spacing(15);
    mainLayout->set_column_spacing(15);
    mInputs.emplace_back(make_managed<CoordVec<UTMREF>>(*this, UTMREF(), CoordType::eUTMREF));
    mInputs.emplace_back(make_managed<CoordVec<UTM>>(*this, UTM(), CoordType::eUTM));
    mInputs.emplace_back(make_managed<CoordVec<LLHInt>>(*this, LLHInt(), CoordType::eLLH));
    mInputs.emplace_back(make_managed<CoordVec<LocalCoordinates>>(*this, LocalCoordinates(), CoordType::eLOCAL));
    
    for(auto& input : mInputs){
        auto it = find (mInputs.begin(), mInputs.end(), input);
        if (it == mInputs.end()){
                std::runtime_error("failed to find Index of CoordVec");
        } 
        else{
                auto idx = std::distance(mInputs.begin(), it);
                std::visit([&, idx](auto&& e)mutable{mainLayout->attach(*e, 1, idx);
                                                     mainLayout->attach(*e->getLabel(), 0, idx);
                                                    },
                                            input);
        }
    }
    for(uint8_t i = 0; i < mInputs.size()*2-1; i++) //insert linespacing
    {
      if(i%2 == 1){
        mainLayout->insert_row(i);
        mainLayout->attach(*make_managed<Label>("_____________________________________________________________________________"), 1, i);
        }   
    }
    pack_start(*mainLayout);
    mainLayout->show_all();
}

template<typename Y>
void CoordTrafoIO::inputChanged(CoordType eType, Y coords)
{
    for(auto& input : mInputs){
        std::visit([eType, coords](auto&& e){if(e->getCoordType() != eType){
                                     e->onCoordsChanged(eType, coords);};
                                    },
                                    input);
    }
}
