#include "org_sikuli_script_LinuxUtil.h"
#include <jni.h>
#include <cstring>
#include <iostream>
#include <X11/Xlib.h>

static Display* display = NULL;
static jclass clazz = NULL;
static jmethodID init = NULL;

void checkJNI(JNIEnv* env)
{
  if (display == NULL) {
    display = XOpenDisplay(NULL);
  }
  clazz = env->FindClass("org/sikuli/script/Window");
  init = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;JIIII)V");
}

JNIEXPORT jobject JNICALL Java_org_sikuli_script_LinuxUtil_getX11FocusedWindow
  (JNIEnv* env, jclass)
{
  checkJNI(env);

  XWindowAttributes attrs;
  Window root, child;
  int holder;
  char* name;

  XQueryPointer(display, DefaultRootWindow(display), &root, &child,
      &holder, &holder, &holder, &holder, (unsigned int*)&holder);
  XGetWindowAttributes(display, child, &attrs);
  XFetchName(display, child, &name);

  jobject obj = env->NewObject(clazz, init, env->NewStringUTF(name), child, attrs.x, attrs.y, attrs.width, attrs.height);
  XFree(name);
  return obj;
}

JNIEXPORT jobject JNICALL Java_org_sikuli_script_LinuxUtil_getX11Window__Ljava_lang_String_2
  (JNIEnv* env, jclass, jstring jname)
{
  checkJNI(env);

  const char* name = env->GetStringUTFChars(jname, NULL);
  jobject obj = NULL;
  XWindowAttributes attrs;
  Window root, parent, *children;
  unsigned int nchildren;
  char* buf;
  bool found = false;
  for (int i = 0; i < ScreenCount(display) && !found; ++i) {
    if (XQueryTree(display, RootWindow(display, i), &root, &parent, &children, &nchildren)) {
      for (int j = 0; j < nchildren && !found; ++j) {
        if (XFetchName(display, children[j], &buf)) {
          if (!strcmp(buf, name)) {
            XGetWindowAttributes(display, children[j], &attrs);
            obj = env->NewObject(clazz, init, jname, jint(children[j]), attrs.x, attrs.y, attrs.width, attrs.height);
            env->ReleaseStringUTFChars(jname, name);
            found = true;
          }
          XFree(buf);
        }
      }
    }
  }

  return obj;
}

JNIEXPORT jobject JNICALL Java_org_sikuli_script_LinuxUtil_getX11Window__J
  (JNIEnv* env, jclass, jlong id)
{
  checkJNI(env);

  jobject obj = NULL;
  Window window = (Window)id;
  XWindowAttributes attrs;
  char* name;
  if (XFetchName(display, window, &name)) {
    XGetWindowAttributes(display, window, &attrs);
    obj = env->NewObject(clazz, init, env->NewStringUTF(name), id, attrs.x, attrs.y, attrs.width, attrs.height);
    XFree(name);
  }

  return obj;
}
