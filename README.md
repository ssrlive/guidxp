# GUID generator for Cross Platform

Written in pure C. Supporting `Linux`, `iOS`, `macOS`, `Windows`, `Android`.

```
#if defined(ANDROID)
#include <jni.h>
bool generate_guid(JNIEnv *env, char *guid_string, size_t len);
#else
bool generate_guid(char *guid_string, size_t len);
#endif
```

<!--
## Linux
Install the uuid library first by the following command.
```
apt-get install uuid-dev uuid -y
```
or
```
yum install libuuid-devel -y
```
-->
