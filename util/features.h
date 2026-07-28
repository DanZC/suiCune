#pragma once

// Controls whether networking support is enabled.
#ifndef FEATURE_NETWORKING
#define FEATURE_NETWORKING 1
#endif

// Controls whether mobile features are enabled.
#ifndef FEATURE_MOBILE
#if FEATURE_NETWORKING
#define FEATURE_MOBILE 1
#else
#define FEATURE_MOBILE 0
#endif // FEATURE_NETWORKING
#else
#if !FEATURE_NETWORKING && FEATURE_MOBILE
#error "Mobile features cannot be enabled without networking."
#endif
#endif // FEATURE_MOBILE

// Controls whether the time capsule feature is enabled.
#ifndef FEATURE_TIME_CAPSULE
#if !FEATURE_NETWORKING
#define FEATURE_TIME_CAPSULE 0
#endif // FEATURE_NETWORKING
#else
#if !FEATURE_NETWORKING && FEATURE_TIME_CAPSULE
#error "Time capsule cannot be enabled without networking."
#endif
#endif // FEATURE_TIME_CAPSULE
