# Cross Platform GUID generator

Written in C.

```
#if defined(ANDROID)
#include <jni.h>
bool generate_guid(JNIEnv *env, char *guid_string, size_t len);
#else
bool generate_guid(char *guid_string, size_t len);
#endif
```

