#ifndef __XP_GUID_H__
#define __XP_GUID_H__ 1

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(ANDROID)
#include <jni.h>
bool generate_guid(JNIEnv *env, char *guid_string, size_t len);
#else
bool generate_guid(char *guid_string, size_t len);
#endif

#ifdef  __cplusplus
}
#endif

#endif /* __XP_GUID_H__ */
