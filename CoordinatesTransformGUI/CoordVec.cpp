// #include "CoordVec.h"
// #include "SpinBoxInput.h"
// #include "LLH.h"
// #include "UTM.h"
// #include "UTMREF.h"
// #include "LocalRef.h"
// #include "LocalCoordinates.h"
// #include "CoordTransformationIO.h"
// #include <sigc++/signal.h>

// using namespace std;
// using namespace Gtk;
// using sigc::mem_fun;

// template<typename T> CoordVec<T>::CoordVec(CoordTrafoIO& io, T coordType) : Gtk::Box(ORIENTATION_HORIZONTAL), mTCoordType{coordType}, mParent{io}
// {   
//     setLabel();
//     initCoordVec();
// }

// template<typename T> void CoordVec<T>::initCoordVec()
// {
//     set_vexpand(false);
//     set_hexpand(false);
//     for(uint8_t i= 0; i<CoordVecSize; i++){
//         mCoords.at(i) = make_managed<SpinBoxInput>(*this);
//         pack_end(*mCoords.at(i));
//         mCoords.at(i)->signal_value_changed().connect(sigc::bind(mem_fun(mParent, &CoordTrafoIO::inputChanged),mCoords.at(i)->mParentVec.getCoordType()));
//     }
//     show_all_children();
// } 


// template<typename T> void  CoordVec<T>::onCoordsChanged(CoordType inputType)
// {
//     // switch (inputType)
//     // {
//     //     case CoordType::eLOCAL:
//     //         switch (mCoordType)
//     //     {     
//     //         case CoordType::eUTM:
//     //             Local2UTM();
//     //             break;
//     //         case CoordType::eLOCAL:
//     //             break;
//     //         case CoordType::eUTMREF:
//     //             Local2UTMREF();
//     //             break;
//     //         case CoordType::eLLH:
//     //             Local2LLH();
//     //         break;
//     //     }
//     //     break;       
//     //     case CoordType::eUTM:
//     //         switch (mCoordType)
//     //         {
//     //         case CoordType::eLOCAL:
//     //             UTM2Local();
//     //             break;
//     //         case CoordType::eUTM:
//     //             break;
//     //         case CoordType::eUTMREF:
//     //             UTM2UTMREF();
//     //             break;
//     //         case CoordType::eLLH:
//     //             UTM2LLH();
//     //         break;
//     //         }
//     //     break;
//     //     case CoordType::eUTMREF:
//     //         switch (mCoordType)
//     //         {   
//     //         case CoordType::eLOCAL:
//     //             UTMREF2UTM();
//     //             break;
//     //         case CoordType::eUTMREF:
//     //             break;        
//     //         case CoordType::eUTM:
//     //             UTMREF2UTM();
//     //             break;
//     //         case CoordType::eLLH:
//     //             UTMREF2LLH();
//     //         break;
//     //         }
//     //     break;
//     //     case CoordType::eLLH:
//     //         switch (mCoordType)
//     //         {   
//     //         case CoordType::eLOCAL:
//     //             LLH2Local();
//     //             break;
//     //         case CoordType::eLLH:
//     //             break;        
//     //         case CoordType::eUTM:
//     //             LLH2UTM();
//     //             break;
//     //         case CoordType::eUTMREF:
//     //             LLH2UTMREF();
//     //             break;
//     //         }
//     //     break;
//     // }
// }

// template<typename T> void CoordVec<T>::setLabel()
// {
//     // switch (mCoordType)
//     // {
//     //     case CoordType::eLOCAL:
//     //         mLabel->set_text("LOCAL: ");
//     //         break;       
//     //     case CoordType::eUTM:
//     //         mLabel->set_text("UTM: ");
//     //         break;
//     //     case CoordType::eUTMREF:
//     //         mLabel->set_text("UTMREF: ");
//     //         break;
//     //     case CoordType::eLLH:
//     //         mLabel->set_text("LLH: ");
//     //         break;
//     // }
// }

// // void CoordVec::LLH2UTM(){
// //     cout << "LLH2UTM" << endl;
// // }
// // void CoordVec::LLH2UTMREF(){
// //     cout << "LLH2UTMREF" << endl;
// // }
// // void CoordVec::LLH2Local(){
// //     cout << "LLH2Local" << endl;
// // }
// // void CoordVec::Local2UTM(){
// //     cout << "Local2UTM" << endl;
// // }
// // void CoordVec::Local2UTMREF(){
// //     cout << "Local2UTMREF" << endl;
// // }
// // void CoordVec::Local2LLH(){
// //     cout << "Local2LLH" << endl;
// // }
// // void CoordVec::UTM2UTMREF(){
// //     cout << "UTM2UTMREF" << endl;
// // }
// // void CoordVec::UTM2Local(){
// //     cout << "UTM2Local" << endl;
// // }
// // void CoordVec::UTM2LLH(){
// //     cout << "UTM2LLH" << endl;
// // }
// // void CoordVec::UTMREF2UTM(){
// //     cout << "UTMREF2UTM" << endl;
// // }
// // void CoordVec::UTMREF2Local(){
// //     cout << "UTMREF2Local" << endl;
// // }
// // void CoordVec::UTMREF2LLH(){
// //     cout << "UTMREF2LLH" << endl;
// // }
        

