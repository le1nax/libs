#pragma once

#include <gtkmm/spinbutton.h>
#include <limits>
#include "definitions.h"
#include <iostream>

template<typename T>
class CoordVec;

template<typename T, typename I> 
class SpinBoxInput : public virtual Gtk::SpinButton{

  public:
    explicit SpinBoxInput(CoordVec<T>& parent): Gtk::SpinButton(Gtk::Adjustment::create(0.0, std::numeric_limits<I>::lowest(), std::numeric_limits<I>::max())),
                                                 mParentVec{parent}
    {
        initSpinBox();
    }
    

    SpinBoxInput(const SpinBoxInput& a) = delete;
    SpinBoxInput& operator=(const SpinBoxInput& a) = delete;

    SpinBoxInput(SpinBoxInput&& a) = delete;
    SpinBoxInput& operator=(SpinBoxInput&& a) = delete;

    virtual ~SpinBoxInput() = default;

    // const CoordVec& getCoordVec() const {
    //     return mParentVec;
    // }
    CoordVec<T>& mParentVec;

  
  private:
    
    void initSpinBox()
    {
      set_visible();
      if constexpr(std::numeric_limits<T>::is_integer) {
            set_digits(0);
        }
        else{
          set_digits(doublePrecision);
        }
    }

  public: //slots

    void onCoordsChanged()
    {
      std::cout << "changed" << std::endl;
    }

    void setValue(I value) {
        this->set_value(static_cast<double>(value));
    }

    I getValue() const {
        return static_cast<T>(this->get_value());
    }
};