#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "xp-guid.h"

#if defined(ANDROID) // any Android distribution
#include <jni.h>
#include <cassert>
#define GUID_ANDROID
#elif defined(__linux__) // any Linux distribution
#include <uuid/uuid.h>
#define GUID_LIBUUID
#elif defined(APPLE) // macOS or iOS system
#include <CoreFoundation/CFUUID.h>
#define GUID_CFUUID
#elif defined(_WIN32) // Windows system
#include <objbase.h>
#define GUID_WINDOWS
#else
#error "Unknow platform"
#endif

#ifdef GUID_LIBUUID
bool generate_guid(char *guid_string, size_t len) {
    uuid_t uuid;
    if (guid_string==NULL || len<37) {
        return false;
    }
    uuid_generate(uuid);
    memset(guid_string, 0, len);
    uuid_unparse_lower(uuid, guid_string);
    return true;
}
#endif /* GUID_LIBUUID */

#ifdef GUID_CFUUID
bool generate_guid(char *guid_string, size_t len) {
    CFUUIDRef uuidRef;
    CFStringRef uuidStrRef;
    CFIndex length;
    CFIndex maxSize;

    if (guid_string == NULL || len < 37) {
        return false;
    }

    uuidRef = CFUUIDCreate(kCFAllocatorDefault);
    uuidStrRef= CFUUIDCreateString(kCFAllocatorDefault, uuidRef);
    CFRelease(uuidRef);

    length = CFStringGetLength(uuidStrRef);
    maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8) + 1;
    if (len < (size_t)maxSize) {
        return false;
    }
    CFStringGetCString(uuidStrRef, guid_string, maxSize, kCFStringEncodingUTF8);

    CFRelease(uuidStrRef);

    return true;
}
#endif /* GUID_CFUUID */

#ifdef GUID_WINDOWS
bool generate_guid(char *guid_string, size_t len) {
    GUID guid = {0};
    wchar_t szGuidW[40] = {0};
    if (guid_string == NULL || len < 37) {
        return false;
    }
    CoCreateGuid(&guid);
    StringFromGUID2(&guid, szGuidW, 40);
    WideCharToMultiByte(CP_ACP, 0, szGuidW, -1, guid_string, len, NULL, NULL);
    return true;
}
#endif /* GUID_WINDOWS */

#ifdef GUID_ANDROID
bool ConvertJString(JNIEnv* env, jstring str, char *buffer, size_t buffer_len);

bool generate_guid(JNIEnv *env, char *guid_string, size_t len) {
    jclass uuidClass;
    jmethodID newGuidMethod;
    jmethodID toStringMethod;

    // uniqueId = UUID.randomUUID().toString(); 

    jclass localUuidClass = env->FindClass("java/util/UUID");
    uuidClass = (jclass)env->NewGlobalRef(localUuidClass);
    env->DeleteLocalRef(localUuidClass);
    newGuidMethod = env->GetStaticMethodID(uuidClass, "randomUUID", "()Ljava/util/UUID;");

    jobject javaUuid = env->CallStaticObjectMethod(uuidClass, newGuidMethod);

    toStringMethod = env->GetMethodID(javaUuid, "toString", "()J");
    jstring uuidString = env->CallObjectMethod(javaUuid, toStringMethod);

    bool result = ConvertJString(env, uuidString, guid_string, len);

    env->DeleteLocalRef(javaUuid);

    env->DeleteLocalRef(uuidClass);

    return result;
}

bool ConvertJString(JNIEnv* env, jstring str, char *buffer, size_t buffer_len) {
    bool result = false;
    jsize len;
    const char* strChars = NULL;
    do {
        if (env==NULL || str==NULL || buffer==NULL) {
            break;
        }
        len = env->GetStringUTFLength(str);
        strChars = env->GetStringUTFChars(str, (jboolean *)0);
        if (strChars == NULL) {
            break;
        }
        if (buffer_len < len + 1) {
            break;
        }
        strncpy(buffer, strChars, buffer_len);
        result = true;
    } while (0);
    if (strChars) {
        env->ReleaseStringUTFChars(str, strChars);
    }
    return result;
}

#endif /* GUID_ANDROID */
