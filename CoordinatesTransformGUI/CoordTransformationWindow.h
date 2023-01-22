#pragma once

//gtkmm includes
#include <gtkmm/grid.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/notebook.h>
#include <gtkmm/builder.h>
#include <gtkmm/menubar.h>

//std includes
#include <memory>

//fsd-lib includes
#include <Vec.h>
#include <Log.h>

class CoordTrafoIO;
template<typename T>
class CoordVec;
template<typename T, typename I>
class SpinBoxInput;

class CoordTransformationWindow : public Gtk::ApplicationWindow {


  public:
    CoordTransformationWindow();

    CoordTransformationWindow(const CoordTransformationWindow&) = delete;
    CoordTransformationWindow& operator=(const CoordTransformationWindow&) = delete;

    CoordTransformationWindow(CoordTransformationWindow&&) = delete;
    CoordTransformationWindow& operator=(CoordTransformationWindow&&) = delete;

    //virtual ~ConfigurationsGenerator() override = default;
    virtual ~CoordTransformationWindow() override;

    private: 
    
    std::unique_ptr<CoordTrafoIO> io_overlay{nullptr};
    void initMainLayout();


};
