#ifndef CALIBRATION__VISIBILITY_CONTROL_H_
#define CALIBRATION__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define CALIBRATION_EXPORT __attribute__ ((dllexport))
    #define CALIBRATION_IMPORT __attribute__ ((dllimport))
  #else
    #define CALIBRATION_EXPORT __declspec(dllexport)
    #define CALIBRATION_IMPORT __declspec(dllimport)
  #endif
  #ifdef CALIBRATION_BUILDING_DLL
    #define CALIBRATION_PUBLIC CALIBRATION_EXPORT
  #else
    #define CALIBRATION_PUBLIC CALIBRATION_IMPORT
  #endif
  #define CALIBRATION_PUBLIC_TYPE CALIBRATION_PUBLIC
  #define CALIBRATION_LOCAL
#else
  #define CALIBRATION_EXPORT __attribute__ ((visibility("default")))
  #define CALIBRATION_IMPORT
  #if __GNUC__ >= 4
    #define CALIBRATION_PUBLIC __attribute__ ((visibility("default")))
    #define CALIBRATION_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define CALIBRATION_PUBLIC
    #define CALIBRATION_LOCAL
  #endif
  #define CALIBRATION_PUBLIC_TYPE
#endif

#ifdef __cplusplus
}
#endif

#endif  // CALIBRATION__VISIBILITY_CONTROL_H_