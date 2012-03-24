#include "org_sikuli_script_LinuxUtil.h"
#include <jni.h>
#include <cstring>
#include <iostream>
#include <X11/Xlib.h>

static Display* display = NULL;

JNIEXPORT void JNICALL Java_org_sikuli_script_LinuxUtil_init
  (JNIEnv *, jclass)
{
  display = XOpenDisplay(NULL);
}

JNIEXPORT jobject JNICALL Java_org_sikuli_script_LinuxUtil_getX11FocusedWindow
  (JNIEnv *env, jclass)
{
  jclass clazz = env->FindClass("org/sikuli/script/Window");
  jmethodID init = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;IIII)V");

  XWindowAttributes attrs;
  Window root, child;
  int holder;
  char* name;

  XQueryPointer(display, DefaultRootWindow(display), &root, &child,
      &holder, &holder, &holder, &holder, (unsigned int*)&holder);
  XGetWindowAttributes(display, child, &attrs);
  XFetchName(display, child, &name);

  jobject obj = env->NewObject(clazz, init, env->NewStringUTF(name), attrs.x, attrs.y, attrs.width, attrs.height);
  XFree(name);
  return obj;
}
